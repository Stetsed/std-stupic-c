// Copyright (c) Quinn Hooft (Stetsed)
// SPDX-License-Identifier: MIT

#[doc(hidden)]
use core::ptr::slice_from_raw_parts;
use std::ffi::CString;

#[derive(Debug)]
#[repr(C)]
enum MessageType {
    Set,
    Get,
    Check,
    Reset,
}

#[derive(Debug)]
#[repr(C)]
pub struct Packet {
    mode: MessageType,
    other: u8,
    key: Vec<CString>,
    value: Vec<CString>,
}

pub struct RustString {}

impl Packet {
    #[unsafe(no_mangle)]
    pub extern "C" fn get_key(&self, index: usize) -> &CString {
        &self.key[index]
    }
    #[unsafe(no_mangle)]
    pub extern "C" fn get_value(&self, index: usize) -> &CString {
        &self.key[index]
    }
}

/// Takes in an array of bytes, the length of this array, and a struct of type Packet.
///
/// * `input_bytes_ptr` - Array of bytes that has been received for communication
/// * `len` - Length of array pointed to by input_bytes_ptr
/// * `return_struct` - Struct of type Packet that is initialized
///
/// # Safety
///
/// Function has a guarantee to be safe against NULL Pointer and a non-aligned pointer due to it
/// being const and having a type size of 1, however it can still cause undefined behavior because it
/// assumes that the "input_bytes_ptr" is a pointer an array of bytes of length "len"
#[unsafe(no_mangle)]
pub extern "C" fn parse_packet(
    input_bytes_ptr: *const u8,
    len: usize,
    return_struct: &mut Packet,
) -> i8 {
    if input_bytes_ptr.is_null() {
        -1
    } else {
        let input_bytes = unsafe { &*slice_from_raw_parts(input_bytes_ptr, len) };
        let byte = input_bytes[0];
        match (byte & 0b11000000).reverse_bits() {
            0 => {
                return_struct.mode = MessageType::Check;
            }
            1 => {
                return_struct.mode = MessageType::Get;
            }
            2 => {
                return_struct.mode = MessageType::Set;
            }
            3 => {
                return_struct.mode = MessageType::Reset;
            }
            _ => {
                panic!("You somehow got a value that cannot be represented here...")
            }
        };
        let extra_control = (byte & 0b00110000) >> 4;
        return_struct.other = extra_control;
        let _amount_keys = byte & 0b00001111;

        0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn fuckyou() {
        // Call the actual start function that your project implements, based on your target's conventions.
        let packet = Packet {
            mode: MessageType::Get,
            other: 0,
            key: Vec::new(),
            value: Vec::new(),
        };

        println!("{:?}", packet.get_value(0));
    }
}
