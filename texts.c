#include <string.h>
#include <stdlib.h>
#include <time.h>

wchar_t *generate_text(char *type_lang)
{
  srand(time(NULL));
  if (strcmp(type_lang, "Russion") == 0) {
    wchar_t *ru_arr[5];
    ru_arr[0] = L"В 1901 году Тейлор снимала меблированные комнаты в мичиганском городе\n\
Бей-Сити, когда ей попалась на глаза реклама международной Панамериканской\n\
выставки, проходившей в эти дни в Буффало. Помимо прочего посетителям\n\
предлагалось посетить находящийся неподалёку Ниагарский водопад.\n\
Буквально на днях там был совершён очередной трюк: ремесленник Карлайл Грэм,\n\
рекламируя свою новую бочку, уже в пятый раз прокатился внутри неё\n\
по порогам нижнего течения Ниагары, включая труднопроходимый водоворот на\n\
повороте реки.";

    ru_arr[1] = L"Первым известным прообразом сложной машины, как устройства для\n\
преобразования энергии из одного вида в другой, было наливное водяное колесо,\n\
колесо, его с древнейших времён использовали для ирригации древние египтяне\n\
и персы. Это механическое устройство служило для преобразования энергии\n\
падающей воды (гидроэнергии) в энергию вращательного движения.";

    ru_arr[2] = L"Основой устройства механической машины являются механизмы\n\
(например, кривошипно-шатунный механизм как часть паровой машины).\n\
Внешне разные машины могут содержать подобные или схожие механизмы.\n\
Но наиболее важные составляющие, остаются неизменными всегда, во всех\n\
машинах, такие как: двигатель, подвижные части и т. д. Машина состоит из\n\
двигателя как источника энергии (движения), передаточного и исполнительного\n\
устройств и системы управления. Вместе первые три части обычно называют\n\
машинным агрегатом. Механическое передаточное устройство называют\n\
передаточным механизмом, а механическое исполнительное устройство\n\
— исполнительным механизмом.";

    ru_arr[3] = L"Идею нового фильма предложил Яков Костюковский, прочитавший\n\
в журнале «За рубежом» заметку о европейских мошенниках, использовавших для\n\
перевозки ценностей гипсовые повязки, которые накладывались на месте мнимых\n\
переломов. Эта сюжетная канва с перемещением основного действия в СССР\n\
показалась режиссёру интересной,и в марте 1967 года соавторы направили на\n\
киностудию «Мосфильм» сценарную заявку с рабочим названием «Контрабандисты».\n\
Излагая концепцию будущей ленты, кинодраматурги отметили, что Юрий Никулин\n\
сыграет в ней «скромного служащего отнюдь не героического вида и нрава»";

    ru_arr[4] = L"В 1882 году на федеральном уровне был принят Акт об исключении\n\
китайцев, который серьёзно поражал китайцев в правах: по новому закону им\n\
запрещалось как иммигрировать в США, так и проходить натурализацию в стране.\n\
Более того, большинство китайцев более не могли воссоединиться со своими\n\
близкими. В результате население нейборхуда не превышало 4000 человек вплоть\n\
до Второй мировой войны.";

    return ru_arr[rand() % 5];
  }

  if (strcmp(type_lang, "English") == 0) {
    wchar_t *en_arr[5];
    en_arr[0] = L"I never spend much time in school but I taught ladies plenty. It's true\n\
I hire my body out for pay, hey hey. I've gotten burned over Cheryl Tiegs,\n\
blown up for Raquel Welch. But when I end up in the hay it's only hay,\n\
hey hey. I might jump an open drawbridge, or Tarzan from a vine.\n\
Cause I'm the unknown stuntman that makes Eastwood look so fine.";

    en_arr[1] = L"This is my boss, Jonathan Hart, a self-made millionaire, he's quite a guy.\n\
This is Mrs H., she's gorgeous, she's one lady who knows how to take care\n\
of herself. By the way, my name is Max. I take care of both of them, which\n\
ain't easy, cause when they met it was MURDER!";

    en_arr[2] = L"Hong Kong Phooey, number one super guy. Hong Kong Phooey, quicker\n\
than the human eye. He's got style, a groovy style, and a car that just won't\n\
stop. When the going gets tough, he's really rough, with a Hong Kong Phooey\n\
chop (Hi-Ya!). Hong Kong Phooey, number one super guy. Hong Kong Phooey,\n\
quicker than the human eye. Hong Kong Phooey, he's fan-riffic!";

    en_arr[3] = L"Mutley, you snickering, floppy eared hound. When courage is needed,\n\
you're never around. Those medals you wear on your moth-eaten chest should be\n\
there for bungling at which you are best. So, stop that pigeon, stop that\n\
pigeon, stop that pigeon, stop that pigeon, stop that pigeon, stop that\n\
pigeon, stop that pigeon. Howwww! Nab him, jab him, tab him, grab him, stop\n\
that pigeon now.";

    en_arr[4] = L"It took seven years of planning and 70,000 volunteers to make\n\
everything go well. Many people have said that the organisation was not as\n\
perfect as that of the Beijing Games, but there was a much better atmosphere\n\
which spread out through the whole city. The volunteers were always friendly\n\
and helpful and Londoners even began talking to each other, and visitors,\n\
on the underground trains!";

    return en_arr[rand() % 5];
  }
}
