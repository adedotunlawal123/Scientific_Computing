use std::env;
use std::process;
use std::thread;
use std::time::SystemTime;

struct Rng64 {
    multiplier: u64,
    increment: u64,
    state: u64,
}

#[allow(dead_code)]
impl Rng64 {
    fn knuth(seed: u64) -> Rng64 {
        Rng64 {
            multiplier: 6364136223846793005,
            increment: 1442695040888963407,
            state: seed,
        }
    }
    fn lcg64(seed: u64) -> Rng64 {
        Rng64 {
            multiplier: 2862933555777941757,
            increment: 1013904243,
            state: seed,
        }
    }
    fn new(a: u64, c: u64, seed: u64) -> Rng64 {
        Rng64 {
            multiplier: a,
            increment: c,
            state: seed,
        }
    }
    fn next(&mut self) -> u64 {
        // X_{n+1} = a*X_n + c (mod m)
        // self.state = self.state*self.multiplier + self.increment;
        self.state = self
            .state
            .wrapping_mul(self.multiplier)
            .wrapping_add(self.increment);
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
    let args: Vec<String> = env::args().collect();
    if args.len() != 5 {
        eprintln!("Usage: pi --threads # --samples #");
        process::exit(1);
    }
    let mut num_threads = 8;
    let mut num_samples = 2500;
    for (i, a) in args.iter().enumerate() {
        if a == "--threads" {
            num_threads = args[i + 1].parse().expect("The desired number of threads.");
        } else if a == "--samples" {
            num_samples = args[i + 1].parse().expect("The desired number of samples.");
        }
    }
    eprintln!(
        "Running with {} threads and {} samples per thread.",
        num_threads, num_samples
    );
    let now_seed = (SystemTime::now()
        .duration_since(SystemTime::UNIX_EPOCH)
        .unwrap()
        .as_millis()
        << 64
        >> 64) as u64;

    let mut children = vec![];
    for k in 0..num_threads {
        children.push(thread::spawn(move || -> f64 {
            eprintln!("Spawing thread #{}", k);
            let mut r = Rng64::lcg64(now_seed + k);
            let mut hits = 0;
            for _ in 0..num_samples {
                let x = 2.0 * r.float() - 1.0;
                let y = 2.0 * r.float() - 1.0;
                if x * x + y * y < 1.0 {
                    hits += 1;
                }
            }
            4.0 * (hits as f64) / (num_samples as f64)
        }));
    }

    let mut intermediate_sums = vec![];
    for child in children {
        // collect each child thread's return value
        let intermediate_sum = child.join().unwrap();
        intermediate_sums.push(intermediate_sum);
    }

    let tally:f64 = intermediate_sums.iter().sum();

    println!("{}", tally / (num_threads as f64));
}
