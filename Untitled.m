
f = 984;

fd = 3200;
N      = 4;    % Order
Fstop1 = f-22;  % First Stopband Frequency
Fstop2 = f+22;  % Second Stopband Frequency
Astop  = 60;   % Stopband Attenuation (dB)

% Construct an FDESIGN object and call its CHEBY2 method.
h  = fdesign.bandpass('N,Fst1,Fst2,Ast', N, Fstop1, Fstop2, Astop, fd);
Hd1 = design(h, 'cheby2');

pnorm  = 'linf';  % Pth Norm
maxnum = 2;       % Maximum Numerator
numcon = 'None';  % Numerator Constraint
omode  = 'Wrap';  % Overflow Mode
svcon  = 'Unit';  % Scale Value Constraint

scale(Hd1, pnorm, ...
    'MaxNumerator', maxnum, ...
    'NumeratorConstraint', numcon, ...
    'Overflowmode', omode, ...
    'ScaleValueConstraint', svcon, ...
    'SOSReorder', 'none');


f = 966;

fd = 3200;
N      = 4;    % Order
Fstop1 = f-22;  % First Stopband Frequency
Fstop2 = f+22;  % Second Stopband Frequency
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


fvtool(Hd,Hd1)
