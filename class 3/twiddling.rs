fn main() {
    let mut byte:u8 = 0b0000_0000;

    byte |= 0b0100_0100;
    println!("{:08b}",byte);
    println!(" ^   ^  ");
    println!("set the 3rd and 7th bits\n");

    byte = !byte; // ~byte in C/C++, complement
    println!("{:08b}",byte);
    println!("^^^^^^^^");
    println!("flip all bits\n");

    byte &= !0b1000_0000;
    println!("{:08b}",byte);
    println!("unset the most significant bit\n");

    byte ^= 0b000_1111;
    println!("{:08b}",byte);
    println!("    ^^^^");
    println!("toggle for 4 least significant bits\n");

    byte <<= 3;
    println!("{:08b}",byte);
    println!("<--<--<0");
    println!("shift bits left 3 positions (zero fill)\n");

    byte >>=2;
    println!("{:08b}",byte);
    println!("0>->->->");
    println!("shift bits right 2 positions (zero fill)\n");

    byte |= 0b1000_0001;
    println!("{:08b}",byte);
    println!("^      ^");
    println!("set the lowest and highest bits");

    byte = byte.rotate_left(2); // cycle bits 2 positions to the left
    println!("{:08b}",byte);
    println!("-<-<-<-<");
    println!("cycle bits 2 positions to the left");
}
