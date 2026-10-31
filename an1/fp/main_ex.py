from datetime import datetime

data1 = datetime.strptime("2020-07-10", "%Y-%m-%d").date()
data2 = datetime.strptime("2019-10-10", "%Y-%m-%d").date()

print(data1.month)