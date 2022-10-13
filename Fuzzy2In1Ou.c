int pin_pot1 = A0;     // heart pulse sensor
int pin_pot2 = D3;     // ds18b20
int pin_oled = D1, D2; // oled 0.96 inch

include<Fuzzy.h>
    Fuzzy *fuzzy = new Fuzzy();

// Input detak jantung
FuzzySet *ringan = new FuzzySet(0, 0, 49, 98);
FuzzySet *normal = new FuzzySet(78, 98, 140, 160);
FuzzySet *berat = new FuzzySet(140, 189, 200, 200);

// input suhu tubug ds18b20
FuzzySet *suhuHipo = new FuzzySet(30, 30, 33.5, 36.5);
FuzzySet *suhuNormal = new FuzzySet(35.5, 36.5, 37.5, 38.5);
FuzzySet *suhuDemam = new FuzzySet(37.5, 40.5, 45, 45);

// output berupa diagnosa
FuzzySet *dDehidrasi = new FuzzySet(-0.4, 0, 0.4);
FuzzySet *tidakDehidrasi = new FuzzySet(0.1, 0.5, 0.9);

void setup()
{
    // Serial.begin(115200);
    // pinMode(pin_oled, output);

    Serial.begin(9600);
    randomSeed(analogReed(0));

    // fuzzy input1 detak jantung
    FuzzyInput *pulse = new FuzzyInput(1);
    pulse->addFuzzySet(ringan);
    pulse->addFuzzySet(normal);
    pulse->addFuzzySet(berat);
    fuzzy->addFuzzySet(pulse);

    FuzzyInput *temperature = new FuzzyInput(2);
    temperature->addFuzzySet(suhuHipo);
    temperature->addFuzzySet(suhuNormal);
    temperature->addFuzzySet(suhuDemam);
    fuzzy->addFuzzySet(temperature);

    // fuzzy output berupa diagnosa
    FuzzyOutput *oled = new FuzzyOutput(1);
    oled->addFUzzySet(dDehidrasi);
    oled->addFuzzy(tidakDehidrasi);
    fuzzy->addFuzzyOutput(oled);
    //////////////////////////////////////////////////////////////////////////
    // rule1
    FuzzyRuleAntecedent *ringan_suhuHipo = new FuzzyRuleAntecedent();
    ringan_suhuHipo->joinWithAND(ringan, suhuHipo);
    FuzzyRuleConsequent *oled_dDehidrasi1 = new FuzzyRuleConsequent();
    oled_dDehidrasi1->addOutput(dDehidrasi);
    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ringan, suhuHipo, oled_dDehidrasi1);
    fuzzy->addFuzzyRule(duzzyRule1);

    // rule2
    FuzzyRuleAntecedent *normal_suhuHipo = new FuzzyRuleAntecedent();
    normal_suhuHipo->joinWithAND(normal, suhuHipo);
    FuzzyRuleConsequent *oled_dDehidrasi2 = new FuzzyRuleConsequent();
    oled_dDehidrasi2->addOutput(dDehidrasi);
    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, normal, suhuHipo, oled_dDehidrasi2);
    fuzzy->addFuzzyRule(duzzyRule2);

    // rule3
    FuzzyRuleAntecedent *berat_suhuHipo = new FuzzyRuleAntecedent();
    berat_suhuHipo->joinWithAND(berat, suhuHipo);
    FuzzyRuleConsequent *oled_dDehidrasi3 = new FuzzyRuleConsequent();
    oled_dDehidrasi3->addOutput(dDehidrasi);
    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, berat, suhuHipo, oled_dDehidrasi3);
    fuzzy->addFuzzyRule(duzzyRule3);

    // rule4
    FuzzyRuleAntecedent *ringan_suhuNormal = new FuzzyRuleAntecedent();
    ringan_suhuNormal->joinWithAND(ringan, suhuNormal);
    FuzzyRuleConsequent *oled_tidakDehidrasi4 = new FuzzyRuleConsequent();
    oled_tidakDehidrasi4->addOutput(tidakDehidrasi);
    FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ringan, suhuNormal, oled_tidakDehidrasi4);
    fuzzy->addFuzzyRule(duzzyRule4);

    // rule5
    FuzzyRuleAntecedent *normal_suhuNormal = new FuzzyRuleAntecedent();
    normal_suhuNormal->joinWithAND(normal, suhuNormal);
    FuzzyRuleConsequent *oled_tidakDehidrasi5 = new FuzzyRuleConsequent();
    oled_tidakDehidrasi5->addOutput(tidakDehidrasi);
    FuzzyRule *fuzzyRule5 = new FuzzyRule(5, normal, suhuNormal, oled_tidakDehidrasi5);
    fuzzy->addFuzzyRule(duzzyRule5);

    // rule6
    FuzzyRuleAntecedent *berat_suhuNormal = new FuzzyRuleAntecedent();
    berat_suhuNormal->joinWithAND(berat, suhuNormal);
    FuzzyRuleConsequent *oled_dDehidrasi6 = new FuzzyRuleConsequent();
    oled_dDehidrasi6->addOutput(dDehidrasi);
    FuzzyRule *fuzzyRule6 = new FuzzyRule(6, berat, suhuNormal, oled_dDehidrasi6);
    fuzzy->addFuzzyRule(duzzyRule6);

    // rule7
    FuzzyRuleAntecedent *ringan_suhuDemam = new FuzzyRuleAntecedent();
    ringan_suhuDemam->joinWithAND(ringan, suhuDemam);
    FuzzyRuleConsequent *oled_dDehidrasi7 = new FuzzyRuleConsequent();
    oled_dDehidrasi7->addOutput(dDehidrasi);
    FuzzyRule *fuzzyRule17 = new FuzzyRule(7, ringan, suhuNormal, oled_dDehidrasi7);
    fuzzy->addFuzzyRule(duzzyRule7);

    // rule8
    FuzzyRuleAntecedent *normal_suhuDemam = new FuzzyRuleAntecedent();
    normal_suhuDemam->joinWithAND(normal, suhuDemam);
    FuzzyRuleConsequent *oled_dDehidrasi8 = new FuzzyRuleConsequent();
    oled_dDehidrasi8->addOutput(dDehidrasi8);
    FuzzyRule *fuzzyRule8 = new FuzzyRule(8, normal, suhuDemam, oled_dDehidrasi8);
    fuzzy->addFuzzyRule(duzzyRule8);

    // rule9
    FuzzyRuleAntecedent *berat_suhuDemam = new FuzzyRuleAntecedent();
    berat_suhuDemam->joinWithAND(berat, suhuDemam);
    FuzzyRuleConsequent *oled_dDehidrasi9 = new FuzzyRuleConsequent();
    oled_dDehidrasi9->addOutput(dDehidrasi);
    FuzzyRule *fuzzyRule9 = new FuzzyRule(9, berat, suhuDemam, oled_dDehidrasi9);
    fuzzy->addFuzzyRule(duzzyRule9);
}

void loop()
{
    int input1 = random(0, 200);
    int input2 = random(0, 0.9);

    Serial.println("\n\n\nEntrance: ");
    Serial.print("t\t\tPulse: ");
    Serial.print(iput1);
    Serial.print(", temperature: ");
    Serial.println(input2);

    fuzzy->setInput(1, input1);
    fuzzy->setInput(2, input2);
    fuzzy->fuzzyfy();

    // input1 detak jantung
    Serial.println("Input: ");
    Serial.print("\tPulse: Ringan-> ");
    Serial.print(ringan->getPertinence());
    Serial.print(", Normal-> ");
    Serial.print(normal->getPertinence());
    Serial.print(", Berat-> ");
    Serial.print(berat->getPertinence());

    // input2 suhu tubuh
    Serial.print("\tTemperature: Hipotermia-> ");
    Serial.print(suhuHipo->getPertinence());
    Serial.print(", Suhu Normal-> ");
    Serial.print(suhuNormal->getPertinence());
    Serial.print(",Suhu Demam -> ");
    Serial.print(suhuDemam->getPertinence());

    float output1 = fuzzy->deffuzyfy(1);

    Serial.println("Output: ");
    Serial.print("\tdDehidrasi: Dehidrasi-> ")
        Serial.print(dDehidrasi->getPertinence());
    Serial.print(", tidakDehidrasi-> Tidak Dehidrasi");
    Serial.print(tidakDehidrasi->getPertinence());

    Serial.println("Result: ");
    Serial.print("\t\t\tDiagnosa: ");
    Serial.print(output1);

    delay(10000)
}

// void loop()
// {
//     // int in_pulse = analogRead(pin_pot1);
//     // int in_temperature = analogRead(pin_pot2);

//     int in_pulse = random(0, 200);
//     int in_temperature = random(0, 0.9);

//     Set output value : Diagnosa;

//     fuzzy->setInput(1, in_pulse);
//     fuzzy->setInput(2, in_temperature);

//     int out_oled = fuzzy->defuzzy(1);
//     analogWrite(pin_oled, out_led);

//     Serial.print("pot1  ");
//     Serial.print(in_pulse);
//     Serial.println("  bit");
//     Serial.print("pot2  ");
//     Serial.println("  bit");
//     Serial.print(in_temperature);
//     Serial.println("  bit");

//     Serial.print(in_pulse);
//     Serial.print(" ");
//     Serial.println(in_temperature);
//     Serial.print(" ");

//     Serial.println("Result: ");
//     Serial.print("    oled: ");
//     Serial.println(out_oled);
// }