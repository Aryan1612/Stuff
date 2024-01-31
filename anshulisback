f = @(x,y) [y(2); 3*(y(2)/x)-3*(y(1)/(x^2))+2*x^2*exp(x)]; 
x0 = 1;  y0 = [0;0];

y2 = 4*exp(2);

x = 2;                            
[xs1,ys1] = ode45(f,[x0,x],y0);
fprintf('y(x) = %g\n',ys1(end,1))
s_0 = ys1(end, 1);

x0 = 1;  y0 = [0;1];

x = 2;                            
[xs2,ys2] = ode45(f,[x0,x],y0);
fprintf('y(x) = %g\n',ys2(end,1))
s_1 = ys2(end, 1);

s_2=0;

for i = 1:1000
    s_2 = secant(s_0, s_1);

    s_0 = s_1;
    s_1 = s_2;
    if phi(s_2) < 0.00001
        fprintf('y value = %g\n',y2+phi(s_2))
        break;
    end
end

y_pred=zeros(100,1);

x_pred=zeros(100,1);
g=@(x)2*x*exp(x)*(x-1);
for i=1:100
    x_pred(i)=1+i/100;
    y_pred(i)=g(1+i/100);
end
y_pred

[xd,yd] = ode45(f,[x0,x],[0;s_2]);

plot(xd,yd(:,1),'b',x_pred,y_pred)
title('Solution y(t) of IVP')
xlabel('t'); grid on


function s_i = secant(s_1, s_2)
    s_i = s_2 - (s_2 - s_1)*(phi(s_2))/(phi(s_2) - phi(s_1));
end

function p = phi(s_1)
    f = @(x,y) [y(2); 3*(y(2)/x)-3*(y(1)/(x^2))+2*x^2*exp(x)];

    [xp ,yp] = ode45(f,[1,2],[0;s_1]);
    p = yp(end, 1) - 4*exp(2);
end
