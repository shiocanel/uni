INSERT INTO users (first_name, last_name, email, birth_date, description)
VALUES
    ('Popovici', 'Alexandra', 'alexandra.popovici@example.com', '2005-04-12', 'Sunt studenta la informatica si imi plac cafeaua si cartile'),
    ('Risca', 'Ioan', 'ioan.risca@example.com', '2004-11-03', 'Sunt pasionat de fotbal si jocuri video'),
    ('Potra', 'Georgiana', 'georgiana.potra@example.com', '2004-02-18', 'Ascult muzica indie si imi place sa desenez'),
    ('Rusu', 'Ricardo', 'ricardo.rusu@example.com', '2005-09-09', 'Sunt fan baschet si filme SF'),
    ('Rusti', 'Maria', 'maria.rusti@example.com', '2005-01-26', 'Imi plac animalele si fotografia'),
    ('Ana', 'Claudia', 'claudia.ana@example.com', '2004-06-14', 'Fac voluntariat si sunt pasionata de calatorii'),
    ('Vasilescu', 'Marin', 'antonio.marin@example.com', '2003-12-30', 'Invat programare si sunt mereu curios sa descopar lucruri noi'),
    ('Alexandra', 'Ionescu', 'alexandra.ionescu@example.com', '2005-03-07', 'Imi plac serialele si serile de board games'),
    ('Mihai', 'Popescu', 'mihai.popescu@example.com', '2004-08-22', 'Joc sah si imi place sa rezolv probleme de algoritmica'),
    ('Elena', 'Dumitrescu', 'elena.dumitrescu@example.com', '2005-05-16', 'Sunt pasionata de limbi straine si muzica'),
    ('Andrei', 'Munteanu', 'andrei.munteanu@example.com', '2004-10-11', 'Merg la sala si invat dezvoltare web'),
    ('Daria', 'Ceban', 'daria.ceban@example.com', '2005-12-02', 'Imi plac cafeaua, arta si plimbarile lungi'),
    ('Victor', 'Rotaru', 'victor.rotaru@example.com', '2004-04-29', 'Sunt fan tehnologie si imi place ciclismul'),
    ('Bianca', 'Neagu', 'bianca.neagu@example.com', '2005-08-05', 'Citesc carti fantasy si colectionez plante'),
    ('Stefan', 'Radu', 'stefan.radu@example.com', '2003-07-17', 'Sunt pasionat de masini si jocuri competitive'),
    ('Irina', 'Cojocaru', 'irina.cojocaru@example.com', '2005-02-09', 'Imi place sa gatesc si sa descopar cafenele noi'),
    ('Denis', 'Pavel', 'denis.pavel@example.com', '2004-09-25', 'Ascult rock si imi place sa construiesc proiecte DIY'),
    ('Sofia', 'Munteanu', 'sofia.munteanu@example.com', '2005-06-30', 'Sunt pasionata de dans si filme vechi'),
    ('Matei', 'Dobre', 'matei.dobre@example.com', '2004-01-13', 'Joc tenis si urmaresc Formula 1'),
    ('Ioana', 'Lupu', 'ioana.lupu@example.com', '2005-10-20', 'Iubesc natura si imi place fotografia analogica');

SELECT * FROM users;
SELECT * FROM friendships;

INSERT INTO friendships (id1, id2, friends_from)
VALUES
    (1, 2, '2026-10-19 10:30:00'),
    (6, 7, '2026-10-20 12:00:00'),
    (7, 8, '2026-10-20 12:15:00'),
    (9, 11, '2026-10-21 14:20:00'),
    (10, 12, '2026-10-22 09:10:00'),
    (12, 13, '2026-10-23 10:00:00'),
    (11, 12, '2026-10-23 10:20:00'),
    (9, 12, '2026-10-23 10:30:00'),
    (10, 13, '2026-10-23 10:45:00'),
    (13, 14, '2026-10-24 11:00:00'),
    (14, 15, '2026-10-24 11:10:00'),
    (15, 16, '2026-10-24 11:20:00'),
    (11, 14, '2026-10-24 11:30:00'),
    (13, 15, '2026-10-24 11:40:00'),
    (17, 18, '2026-10-25 16:00:00'),
    (18, 19, '2026-10-25 16:10:00');