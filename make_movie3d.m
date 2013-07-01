function [] = make_movie3d( filepath )

M = csvread(filepath);
% truncate because matlab adds an extra column of 0s after the last column
M = M(1:end, 1:end-1);

% extract coordinates and particle types
type=M(:,1:5:end);
x=M(:,2:5:end);
y=M(:,3:5:end);
z=M(:,4:5:end);
% no emotion
% q=M(:,5:5:end);

% test
% type = [1 2 3;1 2 3;1 2 3;1 2 3;1 2 3;1 2 3;1 2 3;1 2 3;1 2 3;1 2 3;];

s=size(x);
timesteps=s(1);
population=s(2);

width = type;
% set types
for i=1:numel(type)
     if(type(i)==0)
         type(i) = 'o';
         width(i) = 36;
     elseif(type(i)==1)
         type(i) = 'p';
         width(i) = 300;
     else
         type(i)  = 's';
         width(i) = 36;
     end
end

%deprecated
% for j=1:n
%     (cellstr(char(type(j,1:end))')')
% end

for j=1:timesteps
    clf;
    hold on;
    for k=1:population
        scatter3(x(j,k),y(j,k),z(j,k), width(j,k), [0 0 1], char(type(j,k)),'filled'); 
    end
    hold off;
    axis([0 100 0 100 0 100]);
    grid on;
    F(j)=getframe;
end

% movie(F);

end

