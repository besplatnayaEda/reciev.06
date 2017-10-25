fclose(instrfind);
s = serial('COM4');

set(s,'BaudRate',512000,'DataBits',8,'InputBufferSize',256, 'Timeout', 2,'OutputBufferSize', 20);

fopen(s);

comand = 0;
name = 43690;
f1s1 = [1 2 3 4 5];

fwrite(s, CMD('STOP_DATA_TRANSMIT') ,'uint8');
pause(0.001);

% out = fread(s,1,'uint16')
% fwrite(s, name ,'uint16');
% fwrite(s, f1s1 ,'float32');


fclose(s);