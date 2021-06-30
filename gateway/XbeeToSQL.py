from digi.xbee.devices import XBeeDevice
import pymysql
pymysql.install_as_MySQLdb()
import MySQLdb
import time
from datetime import datetime

#open xbee
device = XBeeDevice("/dev/ttyUSB0", 9600)
device.open()

#open database
db = MySQLdb.connect(
      host = '140.112.94.59',
      port = 33306,
      user = 'root',
      passwd = 'taipower',
      db = 'PoSheng') # db設定自己的資料庫名字
cursor = db.cursor() #游標
cursor.execute("select version();")
result = cursor.fetchall()
for row in result:
      print(row[0])

# Define callback.
def my_data_received_callback(xbee_message):
    address = xbee_message.remote_device.get_64bit_addr()
    data = xbee_message.data.decode("utf8")
    print("Received data from %s:\n %s\n" % (address, data))
    if data != "Hello World":
        timestr = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        illu = data[13:data.find('\n')+1]
        temp = data[data.find('\n')+13:]
        # print(illu, temp)
        cursor.execute("INSERT INTO `Test` \
            (`Time`, `Address`, `Temperature`, `Illumination`, `Test`) \
            VALUES ('%s','%s','%s','%s','%s')" % (timestr, address,temp, illu, data))
        db.commit()

# Add the callback.
device.add_data_received_callback(my_data_received_callback)
input("press enter to stop\n")

# Delete the callback
device.del_expl_data_received_callback(my_data_received_callback)
device.close()

#close database
time.sleep(1)
db.close()