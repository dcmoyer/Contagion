function [F] = make_movie2d( filepath )

cellx = 4;
celly = 4;
length = 75;

M = csvread(filepath);
% truncate because matlab adds an extra column of 0s after the last column
M = M(1:end, 1:end-1);

% extract coordinates and particle types
type=M(:,1:5:end);
x=M(:,2:5:end);
y=M(:,3:5:end);
% z=M(:,4:5:end);
% q=M(:,5:5:end);

mx = mean(x');
my = mean(y');

s=size(x);
timesteps=s(1);
population=s(2);

width = type;
% set types
for i=1:numel(type)
     if(type(i)==0)
         type(i) = 'o';
         width(i) = 24;
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
        scatter(x(j,k),y(j,k), width(j,k), [1/2-k/302 3*k/453 1], char(type(j,k)),'filled'); 
    end
    hold off;
% 	axis([mx(j)-10 mx(j)+10 my(j)-10 my(j)+10]);
	axis([mx(j)-40 mx(j)+40 my(j)-40 my(j)+40]);
%     axis([0 500 0 500]);
%     axis([0 cellx*length 0 celly*length]);
    grid on;
    F(j)=getframe;
end

% movie(F,2,24);

end

