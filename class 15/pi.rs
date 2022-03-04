use std::time::SystemTime;
use std::convert::TryInto;

struct Rng64 {
    multiplier: u64,
    increment: u64,
    state: u64
}

#[allow(dead_code)]
impl Rng64 {
    fn knuth(seed: u64) -> Rng64 {
        Rng64 { multiplier: 6364136223846793005,
              increment:  1442695040888963407,
              state:      seed }
    }
    fn lcg64(seed: u64) -> Rng64 {
        Rng64 { multiplier: 2862933555777941757, 
                increment:  1013904243,
                state:      seed }
    }
    fn new(a: u64, c: u64, seed: u64) -> Rng64 {
        Rng64 { multiplier: a, increment: c, state: seed }
    }
    fn next(&mut self) -> u64 {
        // X_{n+1} = a*X_n + c (mod m)
        // self.state = self.state*self.multiplier + self.increment;
        self.state = self.state.wrapping_mul(self.multiplier).wrapping_add(self.increment);
        self.state
    }
    // generate a floating point number draw pseudo-randomly
    // from the uniform distribution on[0,1)
    fn float(&mut self) -> f64 {
        let bitfield = self.next();
        // s eeeeeee mmmmmmmm
        // 0 011...1 xxxx...x
        // \_______/ \______/
        //  12 bits   52 bits
        let mask = 1023_u64 << 52;
        debug_assert_eq!(mask, 1.0_f64.to_bits());
        f64::from_bits((bitfield >> 12) | mask) - 1.0
    }
}

fn main() {
    //let mut r = Rng64::lcg64(1975);
    let now_seed = (SystemTime::now()
        .duration_since(SystemTime::UNIX_EPOCH)
        .unwrap()
        .as_millis() << 64 >> 64) as u64;

    let mut r = Rng64::lcg64(now_seed.try_into().unwrap());
    let num_samples = 1000;
    let mut hits = 0;
    for _ in 0..num_samples {
        let x = 2.0*r.float()-1.0;
        let y = 2.0*r.float()-1.0;
        if x*x + y*y < 1.0 {
            hits += 1;
        }
    }
    println!("pi approx= {:.3}", 4.0*(hits as f64)/(num_samples as f64));
}

