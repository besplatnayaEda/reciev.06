clear all
fclose(instrfind);
s = serial('COM4');

BR = 2;

sec = 20/BR;
smpl = sec*3200;
set(s,'BaudRate',512000,'DataBits',8,'InputBufferSize',4*smpl, 'Timeout', sec+2,'OutputBufferSize', 1);

fs = 8192;
 t1 = 0:1/fs:10-1/fs;

 


%  sig = chirp(tt,700,9,2100);

% tic
%  sound(1*(0.1*sin_n+0.1*sig));
%%
num = 43690;

bin = dec2bin(num);

for i = 1:16-length(bin)
    bin = [num2str(0) bin];
end

fs = 8192;
% fs = 44100;



f2 = 966;
f1 = 984;

t = 0:1/fs:1/BR-1/fs; %one bit time transmission
M = sin(2*pi*f1*t); 
S = sin(2*pi*f2*t); %mark

sig = zeros(1,1*fs);
for j = 1:length(bin)
	if (str2double(bin(j)) == 1)
        if (j == 0)
            sig = horzcat(sig,zeros(1,fs*BR));
        else
            sig = horzcat(sig,M); %#ok<*AGROW>
        end
    else
        sig = horzcat(sig,S);
	end;
end;

sig = horzcat(sig,zeros(1,1*fs));
sig = sig+3*randn(1,length(sig));


%%
sound(1*(0.010*sig));
fopen(s);

tic
fwrite(s, 9 ,'uint8');
out = fread(s,smpl,'float32');
fwrite(s, 10 ,'uint8');
toc
fclose(s);
ratio = 1e-3;
t = linspace(0,sec,length(out));
figure(1)
 plot(t,out,t,ratio*ones(1,length(out)),t,-ratio*ones(1,length(out)));
 grid on
 figure(2)

freq = [900 1000];
[pxx,f] = periodogram(out,[],[],3200);
plot(f,10*log10(pxx))
grid on