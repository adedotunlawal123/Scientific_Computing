fn norm_unsafe(x:f64, y:f64) -> f64 {
    (x*x + y*y).sqrt()
}

fn norm(x:f64, y:f64) -> f64 {
    let xx = x.abs();
    let yy = y.abs();
    if xx > yy {
        let r = yy/xx;
        let one_r2 = 1.+r*r;
        xx*one_r2.sqrt() // |x|sqrt{1+r^2}
    }
    else {
        let r = xx/yy;
        let one_r2 = 1.+r*r;
        yy*one_r2.sqrt()
    }
}

fn quadratic_roots_unsafe(a:f64, b:f64, c:f64) -> (f64, f64) {
    let x = (b*b-4.*a*c).sqrt(); // no error handling
    let x1 = (-b+x)/(2.*a);
    let x2 = (-b-x)/(2.*a);
    (x1, x2)
}

fn quadratic_roots(a:f64, b:f64, c:f64) -> (f64, f64) {
    let x = (b*b-4.*a*c).sqrt();
    let y = if b > 0.0 { -b-x } else { -b+x };
    let x1 = 2.*c/y;
    let x2 = y/(2.*a);
    (x1, x2)
}

fn sinc_unsafe(x:f64) -> f64 {
    x.sin()/x // sin(x)/x
}

fn sinc(x:f64) -> f64 {
    // sinc(x) = sin(x)/x
    //         = (x - x^3/3! + x^5/5! - ... )/x
    //         = 1 - x^2/3! + x^4/5! - ..
    //         = 1 - x^2/6 + x^4/120 - x^6/5040 + ...
    //         = 1 - (1/6)x^2*(1 - (1/20)x^2*(1 - (1/42)x^2*(1 - ...
    let x2 = x*x;
    if x.abs() < 1.0e-6 {
        1. - (1./6.)*x2*(1. - (1./20.)*x2*(1.-(1./42.)*x2))
    } else {
        x.sin()/x
    }
}

fn main()
{
    println!("Norm of a 2-vector:");
    for &(x,y) in [ (1.0,2.0), (2.0,3.0), (3.0, 4.0),
                    (1.5e-2,4.753e3), (-1386., 29.12),
                    (3.1e12, 4.8e13), (3.1e14, 4.85e15) ].iter() {
        println!("|({}, {})| =", x, y);
        println!("     {:+.16e}", norm(x,y));
        println!(" cf. {:+.16e}", norm_unsafe(x,y));
        println!("");
    }

    println!("Roots of a quadratic polynomial:");
    for &(a,b,c) in [ (2., -24., 70.),
                      (0.25, 258.2, 5.3),
                      (0.1, 1.77e4, 2.3e-3) ].iter() {
        println!("{}x^2 + {}x + {} = 0", a, b, c);
        {
           let (x1, x2) = quadratic_roots(a,b,c);
            println!("      x1 = {}; x2 = {}", x1, x2);
        }
        {
           let (x1, x2) = quadratic_roots_unsafe(a,b,c);
            println!(" cf.  x1 = {}; x2 = {}", x1, x2);
        }
    }

    println!("Behaviour of the ratio sinc(x) = sin(x)/x:");
    for &x in [0., 1.0e-12, 1.0e-7, 1.0e-5, 0.1].iter() {
        println!("       x = {}", x);
        println!("sin(x)/x = {}", sinc_unsafe(x));
        println!(" sinc(x) = {}", sinc(x));
    }
}

