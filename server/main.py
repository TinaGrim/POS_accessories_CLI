from flask import Flask, request, render_template
app = Flask(__name__)

@app.route('/')
def welcome():
    return render_template('name.html')
@app.route('/items/<data>',)
def data(data: str):
    Item = {0: 'Anklet',
            1: 'Bracelet',
            2: 'Brooches',
            3: 'Bangles',
            4: 'Belt',
            5: 'Cap',
            6: 'Earrings',
            7: 'Earphone',
            8: 'Glasses',
            9: 'Handbag',
            10: 'Headphone',
            11: 'Hair clips',
            12: 'Necklace',
            13: 'Purse',
            14: 'Ring',
            15: 'Scarf',
            16: 'Scrunchies',
            17: 'Tote bag',
            18: 'Watch',
            19: 'Wallet',
            20: 'Hat'}
    orderList = [Item[i] for i, char in enumerate(data) if char != "0"]

    return render_template('items.html', items=orderList, count=len(orderList))
if __name__ == "__main__":
    app.run(host='0.0.0.0', port=5000,debug=False);
