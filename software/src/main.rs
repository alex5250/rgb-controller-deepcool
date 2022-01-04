extern crate serial;

use chrono::{DateTime, Utc};
use serial::prelude::*;
use std::env;
use std::{thread, time};
use systemstat::{Platform, System};

const SETTINGS: serial::PortSettings = serial::PortSettings {
    baud_rate: serial::Baud115200,
    char_size: serial::Bits8,
    parity: serial::ParityNone,
    stop_bits: serial::Stop1,
    flow_control: serial::FlowNone,
};
fn main() {
    for arg in env::args_os().skip(1) {
        let mut port = serial::open(&arg).unwrap();
        init(&mut port);
        let sys = System::new();
        generate_packet_to_send(&mut port, sys);
    }
}
fn generate_packet_to_send<T: SerialPort>(port: &mut T, sys: System) {
    loop {
        let now: DateTime<Utc> = Utc::now();
        let cpu_temp = sys.cpu_temp().unwrap() as i32;
        println!(
            "{}[INFO] packet sent via uart to controller cpu temperature +: {}C",
            now.to_rfc2822(),
            cpu_temp
        );

        if cpu_temp < 99 {
            let data = format!("load 0{} 1 \r\n", cpu_temp);
            port.write(data.as_bytes()).unwrap();
        } else {
            let data = format!("load {} 1 \r\n", cpu_temp);
            port.write(data.as_bytes()).unwrap();
        }

        thread::sleep(time::Duration::from_millis(5000));
    }
}
fn init<T: SerialPort>(port: &mut T) {
    port.configure(&SETTINGS).unwrap();
}
