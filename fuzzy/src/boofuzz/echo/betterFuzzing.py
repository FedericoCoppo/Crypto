#!/usr/bin/python

from boofuzz import *

host = "127.0.0.1"
port = 9999

s_initialize("echo")
s_string("something")
s_static("\n")

connection = SocketConnection(host, port, proto = "tcp")

f = open("fuzzing.log", "w")
# ~ logger = FuzzLogger(fuzz_loggers = [FuzzLoggerText(file_handle = f)])
logger = FuzzLogger(fuzz_loggers = [FuzzLoggerCsv(file_handle = f)])

target = Target(connection)
target.procmon = pedrpc.Client(host, 26002)
target.procmon_options = {
	"proc_name" : "echo",
	"start_commands" : ["/home/dani/documents/slides/fuzzyTesting/boofuzz/echo/echo"],
	"stop_commands" : ["killall echo"]
}

session = Session(fuzz_data_logger = logger)
session.add_target(target)

session.connect(s_get("echo"))

n = session.num_mutations()
for i in range(n):
	session.fuzz_single_case(i + 1)
	session.total_mutant_index = i + 1
	if target.procmon.post_send() is False:
		session.restart_target(target)
