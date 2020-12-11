var = b'123/4.5'

dataN = var.decode("utf-8")

#dataN = "123/4.5"

data3 = dataN.rstrip("/")
data4 = dataN.lstrip("/")
data5= dataN.split("/")

print(data5)
print(data5[0])
print(type(data5[0]))
