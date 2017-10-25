
clc
clear all
close all


fclose(instrfind);
s = serial('COM5');
set(s,'BaudRate',57600,'DataBits',8);

fopen(s);





send32s.data = 123;
send32s.f1   = 719;
send32s.f2   = 769;
send32s.br   = 1;
send32s.dt   = 25;
send32s.ol   = 25;
send32s.tl   = 600;
send32s.cp   = 60;
send32s.current_limit = 50;
send32s.count_halt_limit = 10;
send32s.capatity_ant1 = 13;
send32s.capatity_ant2 = 12;
send32s.capatity_ant3 = 25;
send32s.capatity_ant4 = 50;


send8s.enable = 1;
send8s.mode = 1;
send8s.softsrart = 1;
send8s.currentlimit = 0;
send8s.diag = 0;
send8s.cap = 1;
send8s.modulation = 1;
send8s.overloadmode = 1;
send8s.ant1 = 1;
send8s.ant2 = 1;
send8s.ant3 = 1;
send8s.ant4 = 1;
send8s.antlevel1 = 1;
send8s.antlevel2 = 0;
send8s.antlevel3 = 0;
send8s.antlevel4 = 1;


send32 = [send32s.data send32s.f1 send32s.f2 send32s.br send32s.dt send32s.ol send32s.tl send32s.cp send32s.current_limit send32s.count_halt_limit send32s.capatity_ant1 send32s.capatity_ant2 send32s.capatity_ant3 send32s.capatity_ant4];
send8  = [send8s.enable send8s.mode send8s.softsrart send8s.currentlimit send8s.diag send8s.cap send8s.modulation send8s.overloadmode send8s.ant1 send8s.ant2 send8s.ant3 send8s.ant4 send8s.antlevel1 send8s.antlevel2 send8s.antlevel3 send8s.antlevel4];
% fwrite(s, send32, 'int32');
% fwrite(s, send8, 'int8');
% 24 - enable

fwrite(s, [10 0 0 0 255 255 255 254], 'uint8');
fclose(s);