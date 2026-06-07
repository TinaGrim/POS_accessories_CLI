import csv
import enum
with open("../Items.csv") as f:
    reader = csv.reader(f)
    dictionary = {i: row[0] for i,row in enumerate(reader)}
    print(dictionary)
