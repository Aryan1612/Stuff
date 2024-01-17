function [b, c, d] = cubic_spline_interpolation(x, y)
    n = length(x);
    h = diff(x);
    
    alpha = zeros(1, n);
    l = zeros(1, n);
    mu = zeros(1, n);
    z = zeros(1, n);
    
    alpha(2:n-1) = 3 * (y(3:n) - y(2:n-1)) ./ h(2:n-1) - 3 * (y(2:n-1) - y(1:n-2)) ./ h(1:n-2);
    
    l(1) = 1;
    mu(1) = 0;
    z(1) = 0;
    
    for i = 2:n-1
        l(i) = 2 * (x(i+1) - x(i-1)) - h(i-1) * mu(i-1);
        mu(i) = h(i) / l(i);
        z(i) = (alpha(i) - h(i-1) * z(i-1)) / l(i);
    end
    
    l(n) = 1;
    z(n) = 0;
    c = zeros(1, n);
    c(n) = 0;
    
    for j = n-1:-1:1
        c(j) = z(j) - mu(j) * c(j+1);
    end
    
    b = (y(2:n) - y(1:n-1)) ./ h - h .* (c(2:n) + 2 * c(1:n-1)) / 3;
    d = (c(2:n) - c(1:n-1)) ./ (3 * h);
end

% Example usage
x_data = [1, 2, 3, 4, 5];
y_data = [2, 3, 5, 8, 10];

[b, c, d] = cubic_spline_interpolation(x_data, y_data);

% Generate a finer x-axis for plotting
x_fine = linspace(min(x_data), max(x_data), 100);

% Evaluate cubic spline at fine x values
y_fine = zeros(1, length(x_fine));
for i = 1:length(x_fine)
    y_fine(i) = evaluate_cubic_spline(x_fine(i), x_data, y_data, b, c, d);
end

% Plot the original data points and the cubic spline approximation
scatter(x_data, y_data, 'o', 'DisplayName', 'Data Points');
hold on;
plot(x_fine, y_fine, '-r', 'DisplayName', 'Cubic Spline Approximation');
xlabel('x');
ylabel('y');
title('Cubic Spline Interpolation Without spline');
legend('show');
grid on;
hold off;

function y = evaluate_cubic_spline(x, x_data, y_data, b, c, d)
    i = find(x >= x_data, 1, 'last');
    if isempty(i)
        i = 1;
    end
    h = x - x_data(i);
    y = y_data(i) + b(i) * h + c(i) * h^2 + d(i) * h^3;
end