
class Sport {

public:

    Sport(string s) {
        m_name = s;
    }

    string name() const {
        return m_name;
    }


    virtual bool isOutdoor() const {
        return true;
    }

    virtual string icon() const = 0;

    virtual ~Sport() {
    }

private:
    string m_name;
};

class Snowboarding : public Sport {
public:

    Snowboarding(string s) : Sport(s) {

    }

    virtual string icon() const {
        return "a descending snowboarder";
    }

    virtual ~Snowboarding() {
        cout << "Destroying the Snowboarding object named " << name() << "." << endl;
    }

};

class Biathlon : public Sport {
public:
    Biathlon(string s, double d) : Sport(s) {
        m_distance = d;
    }

    virtual string icon() const {
        return "a skier with a rifle";
    }

    virtual ~Biathlon() {
        cout << "Destroying the Biathlon object named " << name() << ", distance " << m_distance << " km." << endl;
    }

private:
    double m_distance;
};

class FigureSkating : public Sport {
public:
    FigureSkating(string s) : Sport(s) {

    }

    virtual bool isOutdoor() const {
        return false;
    }

    virtual string icon() const {
        return "a skater in the Biellmann position";
    }

    virtual ~FigureSkating() {
        cout << "Destroying the FigureSkating object named " << name() << "." << endl;
    }

};

