class ClubCommittee {
    constructor(club, name, position) {
        this.club = club;
        this.name = name;
        this.position = position;
    }
}
document.getElementById("committeeForm").addEventListener("submit", function(e) {
    e.preventDefault();

    let club = clubName.value.trim();
    let name = memberName.value.trim();
    let position = this.position.value.trim();

    if (club === "" || name === "" || position === "") {
        alert("All fields are required!");
        return;
    }
    let member = new ClubCommittee(club, name, position);
    addCommitteeRow(member);
    this.reset();
});

function addCommitteeRow(member) {
    let row = `
        <tr>
            <td>${member.club}</td>
            <td>${member.name}</td>
            <td>${member.position}</td>
        </tr>`;
    committeeTable.innerHTML += row;
}

