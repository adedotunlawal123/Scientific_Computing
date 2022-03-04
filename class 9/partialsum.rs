// sum_{k=1}^N 1/k^p

fn main()
{
    let p:f64 = std::env::args().nth(1).expect("").parse().expect("");

    let keyval = vec![10, 14, 20, 28, 40, 56, 80, 112, 160, 224, 320, 448, 640, 896, 1280, 1792, 2560];

    let topmost = keyval.len()-1;
    let maxval = keyval[topmost];
    let mut i = 0;
    let mut sum = 0.0;
    for k in 1..=maxval {
        let incr = 1.0/(k as f64).powf(p);
        sum += incr;
        if k == keyval[i] {
            println!("{} {}", k, sum);
            i += 1;
        }
    }
}
