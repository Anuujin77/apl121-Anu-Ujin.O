/*
 * APL121 · Бие даалт №1 — Code Quest
 * Сэдэв №5: Агаарын чанар (PM2.5 → AQI ангилал)
 * 7 өдрийн PM2.5 утгыг уншиж, ангилал + тэмдэг бүхий хүснэгт хэвлээд,
 * хамгийн бохир 3 өдрийг эрэмбэлж гаргана.
 */
#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif

/* Функц 1: PM2.5 утгаас AQI ангилал буцаана (US EPA 2024 хил) */
const char *Category(double p) {
    const char *c;
    if (p <= 9) {
        c = "Сайн";
    } else if (p <= 35.4) {
        c = "Дунд зэрэг";
    } else if (p <= 55.4) {
        c = "Эмзэг бүлэгт хортой";
    } else if (p <= 125.4) {
        c = "Хортой";
    } else if (p <= 225.4) {
        c = "Маш хортой";
    } else {
        c = "Аюултай";
    }
    return c;
}

/* Функц 2: тэмдэг буцаана. "!" = маш хортой ба түүнээс дээш, "*" = 35.4-өөс их */
const char *Mark(double p) {
    const char *m;
    if (p > 125.4) {
        m = "!";
    } else if (p > 35.4) {
        m = "*";
    } else {
        m = "";
    }
    return m;
}

int main(void) {
#ifdef _WIN32
    SetConsoleOutputCP(65001); /* Windows терминалд кирилл үсэг зөв харуулах (UTF-8) */
#endif

    /* 1. Хувьсагч зарлах */
    double pm[7];      /* 7 өдрийн PM2.5 утга */
    int day[7];        /* өдрийн дугаар (эрэмбэлэхэд хамт зөөгдөнө) */
    int i, j, tmpD;
    double tmpP;
    int ok;            /* scanf амжилттай уншсан эсэх */
    int ch;
    const char *cat;
    const char *mark;

    /* 2. 7 өдрийн PM2.5 оруулах + шалгах (дүрэм: 0-1000) */
    for (i = 0; i <= 6; i++) {
        printf("Өдөр %d PM2.5 (0-1000):\n", i + 1);
        ok = scanf("%lf", &pm[i]);
        while (ok != 1 || pm[i] < 0 || pm[i] > 1000) {
            if (ok == EOF) {
                return 1;  /* оролт дууссан бол гарна */
            }
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* буруу мөрийг цэвэрлэх (жишээ нь "abc") */
            }
            printf("Буруу утга! 0-1000 хооронд оруулна уу:\n");
            ok = scanf("%lf", &pm[i]);
        }
        day[i] = i + 1;
    }

    /* 3. Хүснэгт: функц дуудаж ангилал, тэмдэг авна */
    printf("Өдөр | PM2.5 | Ангилал | Тэмдэг\n");
    for (i = 0; i <= 6; i++) {
        cat = Category(pm[i]);
        mark = Mark(pm[i]);
        printf("%d | %g | %s | %s\n", day[i], pm[i], cat, mark);
    }

    /* 4. Эрэмбэлэх (bubble sort, ихээс бага): хөрш хоёрыг харьцуулж,
          зүүн нь бага бол солино. pm болон day хамт солигдоно. */
    for (i = 0; i <= 5; i++) {
        for (j = 0; j <= 5 - i; j++) {
            if (pm[j] < pm[j + 1]) {
                tmpP = pm[j];
                pm[j] = pm[j + 1];
                pm[j + 1] = tmpP;
                tmpD = day[j];
                day[j] = day[j + 1];
                day[j + 1] = tmpD;
            }
        }
    }

    /* 5. Хамгийн бохир 3 өдөр */
    printf("Хамгийн бохир 3 өдөр:\n");
    for (i = 0; i <= 2; i++) {
        printf("%d. Өдөр %d — %g\n", i + 1, day[i], pm[i]);
    }

    return 0;
}
