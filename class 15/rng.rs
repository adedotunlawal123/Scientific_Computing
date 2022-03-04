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
    let mut r = Rng64::lcg64(1975);

    for _ in 0..100 {
        //println!("{}", r.next());
        //println!("{:064b}", r.next());
        println!("{}", r.float());
    }
}

