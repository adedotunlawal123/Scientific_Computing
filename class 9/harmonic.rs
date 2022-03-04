fn main()
{
    let n:u32 = std::env::args().nth(1)
        .expect("Specify the number of terms in the partial sum.")
        .parse()
        .expect("Expecting a positive, whole-number argument.");

    let mut sum = 0.0_f32;
    for k in 1..=n {
        sum += 1.0_f32/(k as f32);
    }
    println!("sum 1/k = {}", sum);
    println!("{:0b}", sum.to_bits());
    sum = 0.0;
    for k in 0..n {
        sum += 1.0_f32/((n-k) as f32);
    }
    println!("sum 1/k = {}", sum);
    println!("{:0b}", sum.to_bits());
}
