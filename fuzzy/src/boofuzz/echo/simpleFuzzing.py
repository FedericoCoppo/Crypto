#!/usr/bin/python

from boofuzz import *

host = "127.0.0.1"
port = 9999

s_initialize("echo")
s_string("something")
s_static("\n")

connection = SocketConnection(host, port, proto = "tcp")

target = Target(connection)

session = Session()
session.add_target(target)

session.connect(s_get("echo"))

session.fuzz()
