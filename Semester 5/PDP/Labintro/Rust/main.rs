use std::sync::{Arc, Mutex};
use std::thread;
use std::sync::atomic::{AtomicUsize, Ordering};

// Introduction to Concurrency
fn introduction() {
    thread::spawn(|| {
        println!("Hello from a thread!");
    }).join().unwrap();
}

// Mutex example
fn mutex_example() {
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            let mut num = counter.lock().unwrap();
            *num += 1;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Mutex Example: Result is {}", *counter.lock().unwrap());
}

// Atomic variables example
fn atomic_example() {
    let counter = Arc::new(AtomicUsize::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            counter.fetch_add(1, Ordering::SeqCst);
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Atomic Example: Result is {}", counter.load(Ordering::SeqCst));
}

fn main() {
    println!("--- Introduction to Concurrency ---");
    introduction();

    println!("--- Mutex Example ---");
    mutex_example();

    println!("--- Atomic Variables Example ---");
    atomic_example();
}