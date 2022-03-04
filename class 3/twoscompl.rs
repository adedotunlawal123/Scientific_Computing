fn dotdot() {
    println!("    .");
    println!("    .");
}

fn showbits_u8(x:i32)
{
    println!("{:5} {:08b}", x, (x as u8)); 
}

fn showbits_i8(x:i32)
{
    println!("{:5} {:08b}", x, (x as i8)); 
}

fn main() {
    // unsigned binary
    println!("Ranging 0..255 with type u8 (unsigned 8-bit integer)");
    for x in 0..10 {
        showbits_u8(x);
    }
    dotdot();
    for x in 246..256 {
        showbits_u8(x);
    }
    // two's complement binary
    println!("\nRanging -127..128 with type i8 (signed 8-bit integer)");
    for x in -128..-118 {
        showbits_i8(x);
    }
    dotdot();
    for x in -5..6 {
        showbits_i8(x);
    }
    for x in 118..128 {
        showbits_i8(x);
    }
}
