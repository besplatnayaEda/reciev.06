clear all
clc
fileID = fopen('coef.txt','w');

fd = 3200;              % частота дискретезации
BR = 1;                 % скорость передачи

f1 = 984;
f2 = 960;

% % расчет коеффициентов фнч


N  = 1;    % Order
Fc = 1;  % Cutoff Frequency

h  = fdesign.lowpass('N,F3dB', N, Fc*BR, fd);
Hd = design(h, 'butter', 'FilterStructure', 'df2sos');

reorder(Hd, 'down');

pnorm  = 'l1';    % Pth Norm
maxnum = 2;       % Maximum Numerator
numcon = 'None';  % Numerator Constraint
omode  = 'Wrap';  % Overflow Mode
svcon  = 'Unit';  % Scale Value Constraint

scale(Hd, pnorm, ...
    'MaxNumerator', maxnum, ...
    'NumeratorConstraint', numcon, ...
    'Overflowmode', omode, ...
    'ScaleValueConstraint', svcon, ...
    'SOSReorder', 'none');

% Get the transfer function values.
[b, a] = tf(Hd);

coef_low = [ a(2) a(3) b(1) b(2) b(3)]


% % расчет сетки частот

f0 = [f1 f2];

f = [];
j = 1;
for i = 1:length(f0)
   if mod(f0(i),50) ~= 0
       f(j) = f0(i);
       j = j+1;
   end
end


fprintf(fileID,'\n SETUP.f1 = %4.0f;',f1);
fprintf(fileID,'\n SETUP.f2 = %4.0f;',f2);
fprintf(fileID,'\n SETUP.BR = %4.0f;',BR*10);

Apass = 6;

BW = 1.37;
% % расчет коэффициентов полосового фильтра
for i = 1:length(f)
[bs1, as1, bs2, as2] = bp_gen(f(i), fd, BR);
coef_filt(i,:) = [as1(2) as1(3) bs1(1) bs1(2) bs1(3) as2(2) as2(3) bs2(1) bs2(2) bs2(3)];
if i  == 1
fprintf(fileID,'\n // f = %4.0f , BR = %1.1f\n',f(i), BR);
fprintf(fileID,'/*a1*/   SETUP.cf1s1[0] = %1.15f;\n',as1(2));
fprintf(fileID,'/*a2*/   SETUP.cf1s1[1] = %1.15f;\n',as1(3));
fprintf(fileID,'/*b1*/   SETUP.cf1s1[2] = %1.15f;\n',bs1(1));
fprintf(fileID,'/*b2*/   SETUP.cf1s1[3] = %1.15f;\n',bs1(2));
fprintf(fileID,'/*b3*/   SETUP.cf1s1[4] = %1.15f;\n\n',bs1(3));
		
fprintf(fileID,'/*a1*/   SETUP.cf1s2[0] = %1.15f;\n',as2(2));
fprintf(fileID,'/*a2*/   SETUP.cf1s2[1] = %1.15f;\n',as2(3));
fprintf(fileID,'/*b1*/   SETUP.cf1s2[2] = %1.15f;\n',bs2(1));
fprintf(fileID,'/*b2*/   SETUP.cf1s2[3] = %1.15f;\n',bs2(2));
fprintf(fileID,'/*b3*/   SETUP.cf1s2[4] = %1.15f;\n',bs2(3));

elseif i == 2
fprintf(fileID,'\n // f = %4.0f , BR = %1.1f\n',f(i), BR);
fprintf(fileID,'/*a1*/   SETUP.cf2s1[0] = %1.15f;\n',as1(2));
fprintf(fileID,'/*a2*/   SETUP.cf2s1[1] = %1.15f;\n',as1(3));
fprintf(fileID,'/*b1*/   SETUP.cf2s1[2] = %1.15f;\n',bs1(1));
fprintf(fileID,'/*b2*/   SETUP.cf2s1[3] = %1.15f;\n',bs1(2));
fprintf(fileID,'/*b3*/   SETUP.cf2s1[4] = %1.15f;\n\n',bs1(3));
		
fprintf(fileID,'/*a1*/   SETUP.cf2s2[0] = %1.15f;\n',as2(2));
fprintf(fileID,'/*a2*/   SETUP.cf2s2[1] = %1.15f;\n',as2(3));
fprintf(fileID,'/*b1*/   SETUP.cf2s2[2] = %1.15f;\n',bs2(1));
fprintf(fileID,'/*b2*/   SETUP.cf2s2[3] = %1.15f;\n',bs2(2));
fprintf(fileID,'/*b3*/   SETUP.cf2s2[4] = %1.15f;\n',bs2(3));    
end  

end

fprintf(fileID,'\n // flp = %2.2f , BR = %1.1f\n',Fc*BR, BR);

fprintf(fileID,'/*a1*/   SETUP.cflp[0] = %2.15f;\n',coef_low(1));
fprintf(fileID,'/*a2*/   SETUP.cflp[1] = %2.15f;\n',coef_low(2));
fprintf(fileID,'/*b1*/   SETUP.cflp[2] = %2.15f;\n',coef_low(3));
fprintf(fileID,'/*b2*/   SETUP.cflp[3] = %2.15f;\n',coef_low(4));
fprintf(fileID,'/*b3*/   SETUP.cflp[4] = %2.15f;\n',coef_low(5));

fprintf(fileID,'\n // BR = %1.1f\n', BR);
fprintf(fileID,'SETUP.samplenum = %5.0f;\n',fd/BR);


fclose(fileID);

