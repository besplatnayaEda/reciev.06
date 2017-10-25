function [bs1, as1, bs2, as2] = bp_gen(f, fd, br)

N      = 4;    % Order
Fstop1 = f-22*br;  % First Stopband Frequency
Fstop2 = f+22*br;  % Second Stopband Frequency
Astop  = 60;   % Stopband Attenuation (dB)

% Construct an FDESIGN object and call its CHEBY2 method.
h  = fdesign.bandpass('N,Fst1,Fst2,Ast', N, Fstop1, Fstop2, Astop, fd);
Hd = design(h, 'cheby2');

pnorm  = 'linf';  % Pth Norm
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


Hd.sosMatrix

bs1(1) = Hd.sosMatrix(1,1);
bs1(2) = Hd.sosMatrix(1,2);
bs1(3) = Hd.sosMatrix(1,3);

as1(1) = Hd.sosMatrix(1,4);
as1(2) = Hd.sosMatrix(1,5);
as1(3) = Hd.sosMatrix(1,6);


bs2(1) = Hd.sosMatrix(2,1);
bs2(2) = Hd.sosMatrix(2,2);
bs2(3) = Hd.sosMatrix(2,3);

as2(1) = Hd.sosMatrix(2,4);
as2(2) = Hd.sosMatrix(2,5);
as2(3) = Hd.sosMatrix(2,6);

end
