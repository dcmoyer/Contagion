function [F] = evo_histo_all( pfilepath, gens )

xcenters = 0:4/255:1;
fig = figure;
   set(gcf, 'Position', get(0, 'Screensize'));
f = cell(50, 1);


for i=1:gens
   f{i} = strcat(pfilepath, num2str(i), '.txt');
   M = csvread(f{i});
   % truncate because matlab adds an extra column of 0s after the last column
   M = 1/255 * M(1:end, 1:end-1);
   k = 0;
   for j=[ 7 1:6]
   k = k +1;
   hist(M(:,j), xcenters);
   axis([0 1 0 75]);
   subplot(4,2,k);
   end
    
    F(i)=getframe(fig);

end