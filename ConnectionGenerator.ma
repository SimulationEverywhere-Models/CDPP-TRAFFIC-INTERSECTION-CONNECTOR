[top]
components : connection_generator@ConnectionGenerator
out : out
in : in
in : reset
Link : out@connection_generator out
Link : in in@connection_generator
Link : reset reset@connection_generator

[connection_generator]
distribution : normal
mean : 30
deviation : 8 
timeOut : 00:00:0:001 
zero : 00:00:00:00

