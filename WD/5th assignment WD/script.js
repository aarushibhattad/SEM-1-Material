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
            alert("Name should be grater than 3.");
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






function updateCountdown() {
    const d = new Date();
    console.log(d);
    const endOf2026 = new Date('January 30, 2026 23:59:59');
    const timeDifference = endOf2026 - d;
    console.log(timeDifference);

    if (timeDifference < 0) {
        $('.sf-countdown #days').text("0");
        $('.sf-countdown #hours').text("0");
        $('.sf-countdown #minutes').text("0");
        $('.sf-countdown #seconds').text("0");
        return;
    }

    const days = Math.floor(timeDifference / (1000 * 60 * 60 * 24));
    const hours = Math.floor((timeDifference % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
    const minutes = Math.floor((timeDifference % (1000 * 60 * 60)) / (1000 * 60));
    const seconds = Math.floor((timeDifference % (1000 * 60)) / 1000);

    $('.sf-countdown #days').text(days);
    $('.sf-countdown #hours').text(hours);
    $('.sf-countdown #minutes').text(minutes);
    $('.sf-countdown #seconds').text(seconds);
}

$(document).ready(function() {
   updateCountdown();
   setInterval(updateCountdown, 1000);
});



$("#freezeBtn").click(function () {
    $("#studentForm")
        .find("input, select, textarea, button")
        .prop("disabled", true);

    $("#studentForm").addClass("freeze");
    $("#freezeBtn").text("Form Frozen").prop("disabled", true);
});






$("#modeToggle").click(function () {
    $("body").toggleClass("dark-mode");

    if ($("body").hasClass("dark-mode")) {
        $(this).text("Light Mode");
    } else {
        $(this).text("Dark Mode");
    }
});










