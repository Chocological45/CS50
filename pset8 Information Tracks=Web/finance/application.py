import os
import datetime
import re

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    entries = []

    # Get the purchase data from db
    purchases = db.execute("SELECT stock, SUM(number) FROM purchases JOIN users on purchases.user_id = users.id WHERE user_id = :users_id GROUP BY stock", users_id = session["user_id"])
    for row in purchases:
        symbol = row["stock"]
        name = lookup(symbol)["name"]
        shares = int(row["SUM(number)"])
        price = int(lookup(symbol)["price"])
        total = price * shares

        # Append data to list in dictionary
        entries.append({'symbol' : symbol, 'name' : name, 'shares' : shares, 'price' : price, 'total' : total})

    # Get the users cash
    cash_query = db.execute("SELECT cash FROM users WHERE id = :users_id", users_id = session["user_id"])
    cash = cash_query[0]["cash"]

    # Calculate total cash for the user
    total_purc = db.execute("SELECT stock, number FROM purchases WHERE user_id = :user_id", user_id = session['user_id'])
    total_cash = 0
    for row in total_purc:
        price = lookup(row['stock'])['price']
        total_cash += price*row['number']

    # Send it all to index.html
    return render_template("index.html", cash = cash, entries = entries, total_cash = total_cash+cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    # When stock is requested for purchase
    elif request.method == "POST":

        # Get the stock symbol and number of shares to buy
        symbol = str.upper(request.form.get("symbol"))
        shares = request.form.get("shares")

        # Check symbol is valid
        if lookup(symbol) != None:
            # Get the stock price from lookup
            stock = lookup(symbol)
            price = stock["price"]

            shares_cost = float(shares)*price

            # Get user data
            data = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])

            users_cash = data[0]["cash"]

            if shares_cost > users_cash:
                return apology("Can't Afford", 400)

            else:
                #new_cash = users_cash - shares_cost

                # Deduct the cash of the purchase from users total cash
                db.execute("UPDATE users SET cash = cash - :shares_cost WHERE id = :user_id;", shares_cost = shares_cost, user_id = session["user_id"])


                # Check if stock exists in purchases
                stock_check = db.execute("SELECT * FROM purchases WHERE user_id = :user_id AND stock = :symbol;", user_id = session['user_id'], symbol = symbol)
                if len(stock_check) == 0:
                    # Add purchase to purchase table
                    db.execute("INSERT INTO purchases (stock, number, user_id) VALUES (:symbol, :shares, :user_id);", symbol = symbol, shares = shares, user_id = session["user_id"])

                    # Add purchase to history
                    db.execute("INSERT INTO history (stock, shares, price, user_id, date) VALUES (:stock, :shares, :price, :user_id, :date)", stock = symbol, shares = str(shares), price = price, user_id = session['user_id'], date = datetime.datetime.now())

                    flash('Bought!')
                    return redirect("/")

                elif len(stock_check) == 1:
                    # Update existing purchase
                    db.execute("UPDATE purchases SET number = number + :shares", shares = shares)

                    # Add purchase to history
                    db.execute("INSERT INTO history (stock, shares, price, user_id, date) VALUES (:stock, :shares, :price, :user_id, :date)", stock = symbol, shares = str(shares), price = price, user_id = session['user_id'], date = datetime.datetime.now())

                    flash('Bought!')
                    return redirect("/")

        else:
            return apology("Invalid symbol")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    hist = []

    # Query all history for user
    portfolio = db.execute("SELECT * FROM history WHERE user_id = :user_id;", user_id = session['user_id'])

    # Get data from protfolio
    for row in portfolio:
        sym = row['stock']
        share = row['shares']
        price = row['price']
        date = row['date']

        # Ship it all to history.html
        hist.append({'symbol' : sym, 'shares' : share, 'price' : price, 'date' : date})

    return render_template("history.html", hist = hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
         return render_template("quote.html")

    elif request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Missing Symbol")
        stock = lookup(symbol)
        if stock == None:
            return apology("Invalid Symbol")
        return render_template("quoted.html", name = stock['name'], symbol = stock['symbol'], price = stock['price'])




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Check if details are input correctly
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 403)
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif not request.form.get("confirmation") or request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords don't match", 403)

        # Check db for dupes
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        if len(rows) > 0:
            return apology("NOT Available!", "User is")


        # Check password strength
        length = not(len(request.form.get("password")) <= 6)
        # searching for digits


        case_low = re.search(r"[a-z]", request.form.get("password")) is None
        # searching for uppercase
        case_up = re.search(r"[A-Z]", request.form.get("password")) is None

        # searching for lowercase
        digits = re.search(r"\d", request.form.get("password")) is None

        symbols = re.search(r"\W", request.form.get("password")) is None

        # overall result
        ok = not ( length or digits or case_low or case_up or symbols )

        if ok == True:
            # Insert new user into db
            db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash=generate_password_hash(request.form.get("password")))

            # Continue to the rest of the site
            flash('Registered!')
            return redirect("/")
        else:
            return apology("Password not strong enough :(  Password must have symbol, number, uppercase, lowercase, and minimum length of 6!")

    else:
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        # querying the db
        result = db.execute("SELECT stock FROM purchases WHERE user_id = :user_id GROUP BY stock", user_id = session['user_id'])
        stock = []

        # adding the result to lists to use later
        for item in result:
            stock.append(item['stock'])

        return render_template ("sell.html", stocks=stock)

    elif request.method == "POST":
        # Get the stock symbol and number of shares to buy
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        print("OVERHERE!!!!!!!!!!!!!!!!!!!")
        print(shares)

        if shares == '':
            return apology("Invalid shares")

        if int(float(shares)) < 1:
            return apology ("Invalid shares")

        # Get the stock price from lookup
        if symbol == None:
            return apology("Missing Symbol")
        else:
            stock = lookup(symbol)

        price = stock["price"]


        # Calculate how much cash the user will have after selling their chosen stocks
        #cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"])
        #new_cash = cash[0]['cash'] + (float(shares) * price)

        # Check if they have enough stocks to sell
        num_stocks = db.execute("SELECT number FROM purchases WHERE user_id = :user_id AND stock = :stock", user_id = session['user_id'], stock = symbol)


        if int(shares) <= int(num_stocks[0]['number']):
            # Deduct chosen amount of stocks from purchases
            db.execute("UPDATE purchases SET number = number - :shares WHERE stock = :stock AND user_id = :user_id", shares = int(shares), stock = symbol, user_id = session['user_id'])

            # Give back cash from sale
            db.execute("UPDATE users SET cash = cash + :sale_cash WHERE id = :user_id", sale_cash = (float(shares) * price), user_id = session['user_id'])

            # Add purchase to history
            db.execute("INSERT INTO history (stock, shares, price, user_id, date) VALUES (:stock, :shares, :price, :user_id, :date)", stock = symbol, shares = "-"+str(shares), price = price, user_id = session['user_id'], date = datetime.datetime.now())


            flash('Sold!')
            return redirect("/")

        else:
            return apology("Too many shares")




def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
