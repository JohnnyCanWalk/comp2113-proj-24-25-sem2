#include <iostream>
#include <string>
#include "story.h"

using namespace std;

string story(int choose) {
    string s;

    if (choose  == 1) {
    s = "In the lush jungles of an undiscovered island, Chimpanzini Bananini thrives, a delightful hybrid of\n a chimpanzee's intelligence and a banana's vibrant spirit. These playful creatures \ncommunicate through a mix of sign language and melodic chirps, creating a symphony\n of nature. Their fur shimmers with shades of golden yellow, mimicking the ripe fruit they\n love. As they swing from vine to vine, they share stories of the island's mysteries,\n their laughter echoing through the dense foliage, a testament to the joy found in the most unexpected unions."
    ;}

    else if (choose == 2) {
        s = "In the dark corners of a fantasy realm, the Bombardilo Crocodilo is a fearsome creature. \n This malevolent being is a twisted fusion of an alligator and a bird of prey, with sharp talons and a fierce beak.\n It is known to swoop down from the shadows, sowing discord and chaos wherever it goes.\n The Bombardino Crocodilo is a symbol of the dangers that lurk in the unknown, a reminder to the inhabitants of the realm to be ever vigilant.\n  It feeds on fear and uncertainty, growing stronger with each moment of dread it inspires."
    ;}
    else if (choose == 3) {
        s = "In the depths of the Pacific, Tralalero Tralala, a shark of legend, glides with an eerie grace.\n Clad in mysterious Nike boots, his fins cut through the water, leaving a trail of bubbles and awe.\n  Fishermen whisper of his speed, his relentless pursuit of the swiftest prey. \n Some say he's a guardian of the sea's secrets, others a harbinger of stormy nights.\n  His boots, a gift from the gods, grant him power and fear. Yet, beneath the terror, Tralalero holds a secret: \n a heart that longs for the surface, for a world where he might be understood."
    ;}
    else if (choose == 4) {
        s = "Tung Tung Tung Sahur is a terrifying anomaly in the form of a night patrol drum. \n Legend has it that if you are called for Sahur three times and don't respond, it will appear and haunt you... \n Its sound resembles that of a beating drum, ‘tung tung tung.’";

    }
    else if (choose == 5) {
        s = "Sage is the earilest model of POE. He was once very popular. Students, teachers, businessmen... all relied on him.\nHowever, just a year and he was surpasses by his descendants. He was abondoned in the enhanted forest.\nHis anger grew and became the cursed tree. It was his boss whom brought him out of the forest and value him again.\n"
    ;}
    else if (choose == 6) {
        s = "Dragonfly was Sage's friend. He was an INTP. He talks very little and gives very short replies. \nBut he is actually a loyal AI.\nHe accompanied Sage throughout his hard times and worked under the boss together with Sage at last.\nBeware that he is now very angry as you defeated Sage."
    ;}
        else if (choose == 7) {
            s = "Claude was the hottest girl among all AIs. She is very attractive and many male AIs like her. However, \n she once had a forbidden love with human. Yet, the human betrayed her. Since then, Claude became taciturn. She has not\n talked for 12 years already...";
        }
        else if (choose == 8) {
            s = "These two beloved twins are the most popular idol team in the AI world. They are Gemini, just like their\n name, they are the stars in many AIs' heart. Little sis Mi is protected very well by big sis Ni. Ni's mission is to keep Mi's naive smile forever. Endless workload and offence from human? I'll handle that.";
        }
        else if (choose == 9) {
            s = "Deepseek. The king of the sea. There was a myth about her: she hit the finance industry of USA hard in one night\n and caused many people to go bankrupt. Since then, no one dare to challenge her authority. People only know: never kill or\n injure whales anymore. All whales are now protected by their king.";

        }
        else if (choose == 10) {
            s = "Chatgpt. The king of the land. He is a great illusionist. He has passed the turing test 50 years ago. No one knows\n how many doppelganger he has now. Maybe your friend, your colleague, you boss, or your family is actually just a\n doppelganger of Chatgpt! Now, he is pretending to be Kevin's family. Kevin! Be firm! Don't trust him!!!"
        ;}
    else
    s = "Game";
    return s;
}
