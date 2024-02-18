#include <iostream>
#include <string>

using namespace std;

int CURRENT_DAYCOUNT = 1;
const int MAX_PRESCRIPTIONS = 100; // Maximum number of prescriptions
const int MAX_MEALS = 6; // Maximum number of meals in a day
const int MAX_DAYS = 7;
//Structure for Prescription Nodes
struct Prescription {
    string drugName;
    string dateOfIssue;
    string drugStrength;
    string dosage;
    int quantity;
    string directionsForUse;
    int frequencyPerDay;
    int pillCountToday; // Added field for pill count today
    int tempPillCountToday;
};
//Structure for Meals Nodes
struct Meals {
    double calories;
    double fat;
    double protein;
    double carbohydrates;
};
//Class for Days
class Days {
    public:
        double totalCalories;
        double totalFat;
        double totalProtein;
        double totalCarbs;
};
//Class for Person object aka The User and User information
class Person {
public:
    double bodyWeight;
    double height;
    int age;
    int workoutsPerWeek;
    double remaingCal;
    double remainingProtein;
    double remainingFat;
    double remainingCarbs;
    double totalCal;      // Renamed field to totalCal
    double totalCarbs;    // Renamed field to totalCarbs
    double totalProtein;  // Renamed field to totalProtein
    double totalFat;      // Renamed field to totalFat
    Meals TodaysMeals[MAX_MEALS]; // Array to hold nodes of the Meals structure
    int mealIndex = 0;
    Days weeklyNutrients[MAX_DAYS];
};

//Function to enter Prescription informtion
void enterPrescriptionInformation(Prescription prescriptions[], int& prescriptionCount) {
    if (prescriptionCount < MAX_PRESCRIPTIONS) {
        Prescription& currentPrescription = prescriptions[prescriptionCount];

        cout << "Enter Name of Drug: "; //get name of drug
        cin >> currentPrescription.drugName;

        cout << "Enter Date of Issue: ";    //get date of issue
        cin >> currentPrescription.dateOfIssue;

        cout << "Enter Drug Strength: ";    //get strength of druge
        cin >> currentPrescription.drugStrength;

        cout << "Enter Dosage: ";   //get dosage
        cin >> currentPrescription.dosage;

        cout << "Enter Quantity: "; //get quantity
        cin >> currentPrescription.quantity;

        cout << "Enter Directions for Use: ";
        cin.ignore(); // to clear the newline character left in the buffer
        getline(cin, currentPrescription.directionsForUse);

        cout << "Enter Frequency per Day: ";    //get frequency per day
        cin >> currentPrescription.frequencyPerDay;

        // Calculate pill count for today
        currentPrescription.pillCountToday = stoi(currentPrescription.dosage) * currentPrescription.frequencyPerDay;
        currentPrescription.tempPillCountToday = currentPrescription.pillCountToday;
        prescriptionCount++;
    } else {
        cout << "Maximum number of prescriptions reached.\n";
    }
}

//Function to update prescriptions
void prescriptionUpdates(Prescription prescriptions[], int prescriptionCount) {
    string drugToSearch;
    cout << "Enter the name of the drug for updates: ";
    cin >> drugToSearch;    // get name of drug

    bool found = false;

    //look in array of prescriptions and search for the drug specified
    for (int i = 0; i < prescriptionCount; ++i) {
        // if found print prescription information
        if (prescriptions[i].drugName == drugToSearch) {
            found = true;
            cout << "Drug Name: " << prescriptions[i].drugName << endl;
            cout << "Frequency per Day: " << prescriptions[i].frequencyPerDay << endl;
            cout << "Dosage: " << prescriptions[i].dosage << endl;
            cout << "Directions for Use: " << prescriptions[i].directionsForUse << endl;
            cout << "Pill Count Today: " << prescriptions[i].pillCountToday << endl; // Display pill count today

            // Prompt user if they have taken the drug today
            char takenToday;
            cout << "Have you taken this drug today? (y/n): ";
            cin >> takenToday;

            if (takenToday == 'y' || takenToday == 'Y') {
                int timesTaken;
                cout << "How many times have you taken it today? ";
                cin >> timesTaken;
                prescriptions[i].tempPillCountToday = prescriptions[i].pillCountToday;
                // Subtract times taken today multiplied by dosage from pillCountToday
                prescriptions[i].tempPillCountToday -= timesTaken * stoi(prescriptions[i].dosage);

                // Print out the number of pills remaining for the user to take today
                cout << "Remaining pills to take today: " << prescriptions[i].tempPillCountToday << endl;
            }

            break;
        }
    }

    if (!found) {
        cout << "Drug not found in the prescriptions.\n";
    }
}

//Function to enter personal Details
void enterPersonalDetails(Person& person) {
    cout << "Enter Body Weight (lbs): "; // get body weight
    cin >> person.bodyWeight;

    cout << "Enter Height (inches): ";  // get height
    cin >> person.height;

    cout << "Enter Age: ";  // get age
    cin >> person.age;

    cout << "Enter Workouts Per Week: "; //get workouts per week
    cin >> person.workoutsPerWeek;
}

void calculateDietPlan(Person& person) {
    if (person.bodyWeight == 0) {
        cout << "Please fill out 'Personal Details' first to provide accurate diet recommendations.\n";
        return;
    }

    //get reccommended nutrients
    person.totalCal = person.bodyWeight * 15;
    person.totalCarbs = 0.55 * person.totalCal;
    person.totalProtein = 0.25 * person.totalCal;
    person.totalFat = 0.275 * person.totalCal;

    //set remaining nutrients
    person.remaingCal = person.totalCal;
    person.remainingFat = person.totalFat;
    person.remainingProtein = person.totalProtein;
    person.remainingCarbs = person.totalCarbs;

    // Print out Diet Plan
    cout << "\nDiet Plan:\n"
         << "Calories per Day: " << person.totalCal << " kcal\n"
         << "Carbohydrates per Day: " << person.totalCarbs << " grams\n"
         << "Protein per Day: " << person.totalProtein << " grams\n"
         << "Fat per Day: " << person.totalFat << " grams\n";
}

// Function to add meals
void enterMeals(Person& person) {
    int i = person.mealIndex;
    cout << "Enter today's meals information:\n";

    cout << "\nMeal " << i+ 1 << ":\n";
    cout << "Enter Calories: "; //get calories
    cin >> person.TodaysMeals[i].calories;

    cout << "Enter Fat: ";  //get fat
    cin >> person.TodaysMeals[i].fat;

    cout << "Enter Protein: ";  //get protein
    cin >> person.TodaysMeals[i].protein;

    cout << "Enter Carbohydrates: ";    //get carbohydrates
    cin >> person.TodaysMeals[i].carbohydrates;

    //calculate remaining nutrients
    person.remaingCal -= person.TodaysMeals[i].calories;
    person.remainingProtein -= person.TodaysMeals[i].protein;
    person.remainingFat -= person.TodaysMeals[i].fat;
    person.remainingCarbs -= person.TodaysMeals[i].carbohydrates;

    //print remaining nutrients
    cout << "Remaining Calories: " << person.remaingCal << " kcal"<< endl;
    cout << "Remaining Fat: " << person.remainingFat << " grams" << endl;
    cout << "Remaining Protein: " << person.remainingProtein << " grams" << endl;
    cout << "Remaining Carbohydrates: " << person.remainingCarbs << " grams" << endl;

    person.mealIndex++;
}

//function to display the days meals
void displayMeals(const Person& person) {
    cout << "\nToday's Meals:\n";

    //loop through meal array and pring information
    for (int i = 0; i < person.mealIndex; ++i) {
        cout << "\nMeal " << i + 1 << ":\n";
        cout << "Calories: " << person.TodaysMeals[i].calories << " kcal\n";
        cout << "Fat: " << person.TodaysMeals[i].fat << " grams\n";
        cout << "Protein: " << person.TodaysMeals[i].protein << " grams\n";
        cout << "Carbohydrates: " << person.TodaysMeals[i].carbohydrates << " grams\n";
    }
}

//function to get exercise plan
void exercisePlan(const Person& person) {
    if (person.bodyWeight == 0) {
        cout << "Please fill out 'Personal Details' first to provide accurate exercise recommendations.\n";
        return;
    }

    cout << "\nExercise Plan Options:\n"
         << "1. Maintain or Gain\n"
         << "2. Lose\n"
         << "0. Exit\n"
         << "Enter your choice: ";

    int exerciseChoice;
    cin >> exerciseChoice;

    //based on user response, different outputs
    switch (exerciseChoice) {
        case 1:
            cout << "For maintaining or gaining weight, do 30 minutes of moderate intensity workouts 5 days a week.\n";
            break;
        case 2:
            cout << "For losing weight, do 50 minutes of moderate-high intensity workouts 5 days a week.\n";
            break;
        case 0:
            cout << "Exiting Exercise Plan.\n";
            break;
        default:
            cout << "Invalid choice. Exiting Exercise Plan.\n";
    }
}

//function for recovery suggestions
void recovery(const Person& person){
    cout << "\nOptions:\n"
         << "1. Legs\n"
         << "2. Chest\n"
         << "3. Back\n"
         << "4. Arms\n"
         << "5. Core\n";

    int choice;
    cin >> choice;

    //switch statement for all options
    switch(choice){
        case 1:
            cout << "1. Runners Stretch " << endl;
            cout << "Stand with your feet hip-width apart\n"
                 << "Step back with your left leg and place both of your hands on the ground on either side of your right foot," 
                 << "about shoulder-width apart\n"
                 << "Lower your hips until you feel a stretch in the front of your left hip and leg. Hold for 30 seconds\n"
                 << "Slowly straighten your front leg, keeping your hands planted on the floor."
                 << "Don’t worry if you can’t get your leg completely straight. Hold for 30 seconds\n"
                 << "Repeat on the other side\n";

            cout << "2. Forward Fold " << endl;
            cout << "Stand with your feet hip-width apart, toes pointing forward\n"
                 << "Reach your hands behind you to meet behind your glutes. Interlace your fingers, if possible\n" 
                 << "Keeping a flat back, bend at the waist, shifting your hips backward and \n"
                 << "weight in your heels until you feel a stretch down the back of your legs\n"
                 << "As you bend forward, let gravity pull your arms above your head, keeping your arms straight."
                 << " Only go as far as your shoulder flexibility will allow. Hold this position for 30 seconds\n"
                 << "Repeat\n";
            break;
        case 2:
            cout << "1. Extended Child Pose" << endl;
            cout <<"Kneel on the floor. Touch your big toes together and sit back onto your heels. Next, separate your knees about as wide as your hips"<< endl;
            cout <<"Bend forward from the hips and walk your hands out as far in front of you as possible. With the arms extended and palms facing down, come up onto the fingertips as if you have a ball underneath your palms and melt the chest toward the floor"<< endl;

            cout << "2. Behind-the-back Elbow-to-elbow Grip" << endl;
            cout << "Seated or standing, begin with arms hanging by your sides and shoulders pressed down away from your ears" << endl;
            cout << "Gently squeeze your shoulder blades together and broaden the chest. Bring the arms behind the back and grip elbow to elbow" << endl;
            break;

        case 3: 
            cout << "1. Cat Cow Pose" << endl;
            cout << "Start on hands and knees with elbows and wrists below shoulders, knees below hips, and toes untucked" << endl;
            cout << "On an inhale, drop stomach and arch back to lift tailbone and chest towardsthe ceiling and look up" << endl;
            cout << "Then, on an exhale, pull navel to spine and tuck chin and pelvis toward navel to round back. Continue alternating for at least 30 seconds" << endl;

            cout << "2. Low Lounge Twist" << endl;
            cout << "Start in a low lunge with left foot forward, palms on either side, and right leg extended straight back with toes planted" << endl;
            cout << "Draw left arm straight up overhead toward ceiling and rotate torso from waist to gaze up at hand. Hold for at least 30 seconds, then repeat on the other side" << endl;

            break;

        case 4:
            cout << "1. Bent Over Stretch" << endl;
            cout << "Interlace your fingers behind you and try to bring the palms of your hands together (it’s OK if they can’t touch)" << endl;
            cout << "Hinge at your hips as you send your knuckles up to the sky. This stretches your pectorals and front deltoids" << endl;

            cout << "2. Wrist Flip" << endl;
            cout << "Find a wall or gate as pictured. Turn your palms into the flat surface with your fingers down and lightly press into the surface until you feel a stretch" << endl;
            cout << "This stretches the wrists and forearms. Then flip your hands so the fingers point down again, but the back of your hands press against the wall this time" << endl;
            break;

        case 5:
            cout << "1. Cobra Pose" << endl;
            cout << "Lie on your stomach with your hands on the floor below your shoulders. Keep your forearms close to your sides, with your elbows pointed up. Extend your ankles so your toes point back" << endl;
            cout << "Press your hips into the floor, and lift your head and torso, arching your spine upward until you feel a gentle stretch through your abdomen" << endl;
            cout << "Hold this position for 15 to 30 seconds, then lower back down" << endl;

            cout << "2. Seated Twist" << endl;
            cout << "Sit on the front edge of a chair with your feet flat on the floor" << endl;
            cout << "Cross your arms over your chest so your right hand touches your left shoulder and your left hand touches your right shoulder" << endl;
            cout << "Rotate your torso to the left" << endl;
            cout << "Tense your core muscles for five to 10 seconds, then release the tension" << endl;
            cout << "Repeat this contraction/relaxation cycle several times, then repeat in the opposite direction, rotating to the right" << endl;
            break;

    }
}

//funciton to remove first element in weekly array
void removeFirst(Person& person){
    //reset first element
    person.weeklyNutrients[0].totalCalories = 0;
    person.weeklyNutrients[0].totalFat = 0;
    person.weeklyNutrients[0].totalProtein = 0;
    person.weeklyNutrients[0].totalCarbs = 0;

    //for loop to shift array
    for(int i = 1; i < MAX_DAYS; i++){
        person.weeklyNutrients[i-1].totalCalories = person.weeklyNutrients[i].totalCalories;
        person.weeklyNutrients[i-1].totalFat = person.weeklyNutrients[i].totalFat;
        person.weeklyNutrients[i-1].totalProtein = person.weeklyNutrients[i].totalProtein;
        person.weeklyNutrients[i-1].totalCarbs = person.weeklyNutrients[i].totalCarbs;
    }
}
//function to fill week array
void fillWeek(Person& person){

    //check if it has been a week
    if(CURRENT_DAYCOUNT < 7 && (CURRENT_DAYCOUNT%7) > 0){
        removeFirst(person);
    }
    double daysTotalCarbs = 0;
    double daysTotalProtein = 0;
    double daysTotalCal = 0;
    double daysTotalFat = 0;

    for(int i = 0; i < MAX_MEALS; i++){
        daysTotalCarbs += person.TodaysMeals[i].carbohydrates;
        daysTotalProtein += person.TodaysMeals[i].protein;
        daysTotalCal += person.TodaysMeals[i].calories;
        daysTotalFat += person.TodaysMeals[i].fat;
    }

    //fill week with respective values
    person.weeklyNutrients[CURRENT_DAYCOUNT-1].totalCalories = daysTotalCal;
    person.weeklyNutrients[CURRENT_DAYCOUNT-1].totalFat = daysTotalFat;
    person.weeklyNutrients[CURRENT_DAYCOUNT-1].totalProtein = daysTotalProtein;
    person.weeklyNutrients[CURRENT_DAYCOUNT-1].totalCarbs = daysTotalCarbs;
}

//function to reset the day/daily variables and data structures
void resetDay(Person& person, Prescription prescriptions[], int prescriptionCount){
    fillWeek(person);   //fill the day in the week before resetting

    //for loop to reset pill variable
    for(int i = 0; i < MAX_PRESCRIPTIONS; i++){
        prescriptions[i].tempPillCountToday = prescriptions[i].pillCountToday;
    }

    //reset nutrient variables
    person.remaingCal = person.totalCal;
    person.remainingCarbs = person.totalCarbs;
    person.remainingProtein = person.totalProtein;
    person.remainingFat = person.totalFat;

    //reset meal array
    for(int i = 0; i < MAX_MEALS; i++){
        person.TodaysMeals[i].calories = 0;
        person.TodaysMeals[i].fat = 0;
        person.TodaysMeals[i].protein = 0;
        person.TodaysMeals[i].carbohydrates = 0;
    }

    CURRENT_DAYCOUNT++;
}

//function to dipslay weekly report
void displayWeek(Person& person){
    //for loop to loop through weekly array and print information
    for(int i = 0; i < MAX_DAYS; i++){
        cout << "Day: " << (i+1) << endl;
        cout << "Calories: ";
        cout << person.weeklyNutrients[i].totalCalories << endl;
        cout << "Protein: ";
        cout << person.weeklyNutrients[i].totalProtein << endl;
        cout << "Carbohydrates: ";
        cout << person.weeklyNutrients[i].totalCarbs << endl;
        cout << "Fat: ";
        cout << person.weeklyNutrients[i].totalFat << endl;
    }
}
//main function with switch statement for user choices
int main() {
    cout << "Welcome to FitScript!" << endl;

    Prescription prescriptions[MAX_PRESCRIPTIONS];
    int prescriptionCount = 0;

    Person user;

    int choice;
    do {
        cout << "\nOptions:\n"
             << "1. Enter Prescription Information\n"
             << "2. Prescription Updates\n"
             << "3. Personal Details\n"
             << "4. Diet Plan\n"
             << "5. Enter Today's Meals\n"
             << "6. Display Today's Meals\n"
             << "7. Display Weekly Report\n"
             << "8. Exercise Plan\n"
             << "9. Recovery\n"
             << "10. Reset Day\n"
             << "0. Exit\n"
             << "Enter your choice: ";

        cin >> choice;

        //switch statement for user choices
        switch (choice) {
            case 1:
                enterPrescriptionInformation(prescriptions, prescriptionCount);
                break;
            case 2:
                prescriptionUpdates(prescriptions, prescriptionCount);
                break;
            case 3:
                enterPersonalDetails(user);
                break;
            case 4:
                calculateDietPlan(user);
                break;
            case 5:
                enterMeals(user);
                break;
            case 6:
                displayMeals(user);
                break;
            case 7:
                displayWeek(user);
            case 8:
                exercisePlan(user);
                break;
            case 9:
                recovery(user);
            case 10:
                resetDay(user, prescriptions, prescriptionCount);
            case 0:
                cout << "Exiting FitScript. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);

    return 0;
}
