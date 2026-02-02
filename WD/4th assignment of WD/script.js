function validateForm() {
    const name = document.getElementById('name').value.trim();
    const prn = document.getElementById('prn').value.trim();
    const phone = document.getElementById('phone').value.trim();
    const email = document.getElementById('email').value.trim();

    if (phone.length !== 10 || isNaN(phone)) {
        alert("Phone Number must be exactly 10 digits and numeric.");
        return false;
    }
    
    if (name.length < 3) {
        alert("Name cannot be empty.");
        return false;
    }
    
    if (!/^\d{8}$/.test(prn)) {
        alert("PRN must be 8 digits.");
        return false;
    }
    
    if (!/@.+\./.test(email)) {
        alert("Please enter a valid email format.");
        return false;
    }

    alert("Form submitted successfully!");
    return true;
} 


