#!/usr/bin/python

from boofuzz import *

class MySession(Session):
	def post_send(self, target, fuzz_data_logger, session, sock, *args, **kwargs):
		sent = session.last_send
		received = session.last_recv
		if sent.startswith("user ") and not received.startswith("hello "):
			fuzz_data_logger.log_error("Something if fishy with the user command")
		if sent.startswith("password ") and (not received.startswith("welcome ") and not received.startswith("bye ")):
			fuzz_data_logger.log_error("Something if fishy with the password command")
		if sent.startswith("length ") and not received.startswith("answer "):
			fuzz_data_logger.log_error("Something if fishy with the length command")
		if sent.startswith("isinteger ") and not received.startswith("answer "):
			fuzz_data_logger.log_error("Something if fishy with the isinteger command")
		if sent.startswith("double ") and not received.startswith("answer "):
			fuzz_data_logger.log_error("Something if fishy with the double command")
		if sent.startswith("bye ") and not received.startswith("bye "):
			fuzz_data_logger.log_error("Something if fishy with the bye command")

host = "127.0.0.1"
port = 9999

s_initialize("user")
s_static("user")
s_delim(" ")
s_string("dani")
s_static("\n")

s_initialize("password")
s_static("password")
s_delim(" ")
s_string("security")
s_static("\n")

s_initialize("length")
s_static("length")
s_delim(" ")
s_string("something")
s_static("\n")

s_initialize("isinteger")
s_static("isinteger")
s_delim(" ")
s_string("something")
s_static("\n")

s_initialize("double")
s_static("double")
s_delim(" ")
s_string("something")
s_static("\n")

s_initialize("bye")
s_static("bye")
s_delim(" ")
s_string("dani")
s_static("\n")

connection = SocketConnection(host, port, proto = "tcp")

target = Target(connection)

session = MySession()
session.add_target(target)

session.connect(s_get("user"))
session.connect(s_get("user"), s_get("password"))
session.connect(s_get("password"), s_get("length"))
session.connect(s_get("password"), s_get("isinteger"))
session.connect(s_get("password"), s_get("double"))
session.connect(s_get("password"), s_get("bye"))
session.connect(s_get("length"), s_get("bye"))
session.connect(s_get("isinteger"), s_get("bye"))
session.connect(s_get("double"), s_get("bye"))

session.fuzz()
