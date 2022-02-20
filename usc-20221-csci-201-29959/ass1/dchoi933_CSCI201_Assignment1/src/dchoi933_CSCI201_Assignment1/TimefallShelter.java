package dchoi933_CSCI201_Assignment1;

public class TimefallShelter implements Comparable<TimefallShelter> {
    public int chiralFrequency = -1;
    public boolean timefall = true;
    public String guid = "";
    public String name = "";
    public String phone = "";
    public String address = "";

    @Override
    public int compareTo(TimefallShelter other) {
        return Integer.compare(this.chiralFrequency, other.chiralFrequency);
    }

    @Override
    public String toString() {
        return (
            "Shelter information:\n"
            + "- Chiral frequency: " + this.chiralFrequency + "\n"
            + "- Timefall: " + (this.timefall ? "Current" : "None") + "\n"
            + "- GUID: " + this.guid + "\n"
            + "- Name: " + this.name + "\n"
            + "- Phone: " + this.phone + "\n"
            + "- Address: " + this.address + "\n"
        );
    }
}
