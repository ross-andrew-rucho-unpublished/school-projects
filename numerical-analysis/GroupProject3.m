f1 = @(x) exp(x)./cos(x);
f2 = @(x) (1 + 16*(x).^2).^(-1);

final_error1 = zeros(200, 1);
final_error2 = zeros(200, 1);

for k = 1:200
    n = k;
    x = cos(pi*(0:n)'/n);
    c = [1/2; ones(n-1,1); 1/2].*(-1).^((0:n)');

    xx = linspace(-1,1,5000)';
    numer1 = zeros(size(xx));
    numer2 = zeros(size(xx));
    denom1 = zeros(size(xx));
    denom2 = zeros(size(xx));

    for j = 1:n+1
        xdiff = xx-x(j);
        temp = c(j)./xdiff;
        numer1 = numer1 + temp*f1(x(j));
        numer2 = numer2 + temp*f2(x(j));
        denom1 = denom1 + temp;
        denom2 = denom2 + temp;
    end

    ff1 = numer1./denom1;
    ff2 = numer2./denom2;
    error1 = zeros(size(xx));
    error2 = zeros(size(xx));

    for j = 1:5000
        error1(j) = abs(f1(xx(j)) - ff1(j));
        error2(j) = abs(f2(xx(j)) - ff2(j));
    end
    
    final_error1(k) = max(error1);
    final_error2(k) = max(error2);

end

figure(1);
hold on
plot(1:200, log10(final_error1) );
plot(1:200, log10(final_error2) );
hold off
