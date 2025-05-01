#include <iostream>
#include <string>
#include "story.h"

using namespace std;

string story(int choose) {
    string s;
    if (choose == 1) {
        s = "Sage is the earilest model of POE. He was once very popular. Students, teachers, businessmen... all relied on him.\nHowever, just a year and he was surpasses by his descendants. He was abondoned in the enhanted forest.\nHis anger grew and became the cursed tree. It was his boss whom brought him out of the forest and value him again.\n"
    ;}
    else if (choose == 2) {
        s = "Dragonfly was Sage's friend. He was an INTP. He talks very little and gives very short replies. \nBut he is actually a loyal AI.\nHe accompanied Sage throughout his hard times and worked under the boss together with Sage at last.\nBeware that he is now very angry as you defeated Sage."
    ;}
    else if (choose == 3) {
        s = "Grammarly was the most awkward bot 30 years ago. He was always unemployed so he was often bullied and teased by other bots.\n"
    ;}
    else if (choose == 4) {
        s = "MidJourney is very evil and ambitous. He was very confident of his illustration skills. He thought he should be\nthe world No.1 artist and all other artists whom draw ugly drawings should be unemployed. However, people didn't buy him,\nthey thought his drawings were just copying and it lack diversed style and there are no feelings behind it.\nMidJourney couldn't believe it and he eventually developed ASPD. "
    ;}
    else
    s = "Game";
    return s;
}
