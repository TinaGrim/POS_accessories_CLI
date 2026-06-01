from flask import Flask, request, render_template
app = Flask(__name__)

@app.route('/user/<data>',)
def data(data):
    return f"{data} here is your data"
    #return render_template('name.html')
if __name__ == "__main__":
    app.run(debug=True);
