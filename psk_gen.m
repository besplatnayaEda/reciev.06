clc
clear all



num = 85;

bin = dec2bin(num);

for i = 1:8-length(bin)
    bin = [num2str(0) bin];
end


dev = 0;

f0 = 2400;

time = 10;

PSK_BR = 50;

fd = 48000;%9600;%48000;

t = 0:1/fd:(1/PSK_BR-1/fd-0.5/f0);


M = [sin(2*pi*(f0+dev)*t) zeros(1,fd/(2*f0))]; %mark
n = 1;
sig = zeros(1,fd);
for j = 1:(time*PSK_BR)
    if n == 1
        sig = horzcat(sig,M); %#ok<AGROW>
        n = 2;
    elseif n ==2
        sig = horzcat(sig,-M); %#ok<AGROW>
        n = 1;
    end
end;

sig = horzcat(sig,zeros(1,1*fd));

audiowrite('gen2400_PSK.wav', sig, fd)
figure(1)
plot(sig);
N = (length(sig)+1)/2;
f = (fd/2)/N*(0:N-1);
indxs = find(f>.0e3 & f<2.4e3);
X = goertzel(sig.*(blackman(length(sig))'),indxs);
figure(2)
plot(f(indxs)/1e3,(abs(X)/length(X)));
