class Club {
    constructor(name, category, desc, link) {
        this.name = name;
        this.category = category;
        this.desc = desc;
        this.link = link;
    }

    display() {
        return `
        <div class="col-md-4 mb-4">
            <a href="${this.link}" class="text-decoration-none text-light">
                <div class="club-card">
                    <h3>${this.name}</h3>
                    <p>${this.desc}</p>
                    <span class="badge bg-info">${this.category}</span>
                </div>
            </a>
        </div>`;
    }
}


const clubs = [
    new Club("IEEE", "Technical", "Global technical organization", "1.html"),
    new Club("InnovSphere", "Technical", "Microsoft technologies", "2.html"),
    new Club("Team Quark", "Technical", "Coding & hackathons", "3.html"),
];

$(document).ready(function () {

    clubs.forEach(club => {
        $("#clubContainer").append(club.display());
    });


    $("#clubForm").submit(function (e) {
        e.preventDefault();

        let name = $("#name").val();
        let email = $("#email").val();
        let club = $("#club").val();

        if (name === "" || email === "" || club === "") {
            alert("All fields are required!");
        } else {
            alert("Successfully Registered!");
            this.reset();
        }
    });
});






class SuccessStory {
    constructor(name, club, achievement, image) {
        this.name = name;
        this.club = club;
        this.achievement = achievement;
        this.image = image || "https://via.placeholder.com/300";
    }

    render() {
        return `
        <div class="col-md-4 mb-4">
            <div class="story-card">
                <img src="${this.image}">
                <h4 class="mt-3">${this.name}</h4>
                <p>${this.achievement}</p>
                <span class="badge bg-info">${this.club}</span>
            </div>
        </div>`;
    }
}

$(document).ready(function () {

    $("#storyForm").submit(function (e) {
        e.preventDefault();

        let name = $("#studentName").val().trim();
        let club = $("#clubName").val().trim();
        let achievement = $("#achievement").val().trim();
        let image = $("#imageUrl").val().trim();

        
        if (name === "" || club === "" || achievement === "") {
            alert("All fields except image are mandatory!");
            return;
        }

        let story = new SuccessStory(name, club, achievement, image);

        $("#successContainer")
            .prepend(story.render())
            .children()
            .first()
            .hide()
            .slideDown(800);

        this.reset();
    });

});
