class ClubCommittee {
    constructor(club, name, position) {
        this.club = club;
        this.name = name;
        this.position = position;
    }
}

document.getElementById("committeeForm").addEventListener("submit", function (e) {
    e.preventDefault();

    const club = document.getElementById("clubName").value;
    const name = document.getElementById("memberName").value.trim();
    const position = document.getElementById("position").value.trim();

    if (club === "" || name === "" || position === "") {
        alert("All fields are required!");
        return;
    }

    const member = new ClubCommittee(club, name, position);
    addCommitteeRow(member);

    this.reset();
});

function addCommitteeRow(member) {
    const table = document.getElementById("committeeTable");

    table.innerHTML += `
        <tr>
            <td>${member.club}</td>
            <td>${member.name}</td>
            <td>${member.position}</td>
        </tr>
    `;
}
