import LCS.*;
rng(0,'twister');

% 100 samples of X and Y lengths
r = randi([1 10],1,100);
i = 1;

for n = r
    % Create file for X and Y and close it
    l = pow2(n);
    X = randseq(l,'alphabet','dna');
    Y = randseq(l,'alphabet','dna');
    
    [D, lcs_length, LCS_String] = LCS(X,Y);
    
    Xfilename = sprintf('X%03d.txt', i);
    Yfilename = sprintf('Y%03d.txt', i);
    fid = fopen(Xfilename, 'w');
    fprintf(fid, '%s\n', X);
    fclose(fid);
    
    fid = fopen(Yfilename, 'w');
    fprintf(fid, '%s\n', Y);
    fclose(fid);
    i = i + 1;
    
    fid = fopen('results.txt', 'a');
    fprintf(fid, '%d\n', lcs_length);
    fclose(fid);
    
    fid = fopen('resultslcs.txt', 'a');
    fprintf(fid, '%s\n', LCS_String);
    fclose(fid);
    
end

