#include <string.h>
#include <stdlib.h>
#include <time.h>

wchar_t *generate_text(char *type_lang)
{
  wchar_t *ru_arr[15];
  wchar_t *en_arr[15];

  /* russion texts */
  ru_arr[0] = L"В 1901 году Тейлор снимала меблированные комнаты в мичиганском городе\n\
Бей-Сити, когда ей попалась на глаза реклама международной Панамериканской\n\
выставки, проходившей в эти дни в Буффало. Помимо прочего посетителям\n\
предлагалось посетить находящийся неподалёку Ниагарский водопад.\n\
Буквально на днях там был совершён очередной трюк: ремесленник Карлайл Грэм,\n\
рекламируя свою новую бочку, уже в пятый раз прокатился внутри неё\n\
по порогам нижнего течения Ниагары, включая труднопроходимый водоворот на\n\
повороте реки.";

  ru_arr[1] = L"Основой устройства механической машины являются механизмы\n\
(например, кривошипно-шатунный механизм как часть паровой машины).\n\
Внешне разные машины могут содержать подобные или схожие механизмы.\n\
Но наиболее важные составляющие, остаются неизменными всегда, во всех\n\
машинах, такие как: двигатель, подвижные части и т.д. Машина состоит из\n\
двигателя как источника энергии (движения), передаточного и исполнительного\n\
устройств и системы управления. Вместе первые три части обычно называют\n\
машинным агрегатом. Механическое передаточное устройство называют\n\
передаточным механизмом, а механическое исполнительное устройство\n\
- исполнительным механизмом.";

  ru_arr[2] = L"Идею нового фильма предложил Яков Костюковский, прочитавший\n\
в журнале \"За рубежом\" заметку о европейских мошенниках, использовавших для\n\
перевозки ценностей гипсовые повязки, которые накладывались на месте мнимых\n\
переломов. Эта сюжетная канва с перемещением основного действия в СССР\n\
показалась режиссёру интересной,и в марте 1967 года соавторы направили на\n\
киностудию \"Мосфильм\" сценарную заявку с рабочим названием \"Контрабандисты\".\n\
Излагая концепцию будущей ленты, кинодраматурги отметили, что Юрий Никулин\n\
сыграет в ней \"скромного служащего отнюдь не героического вида и нрава\n\
В обоснование истории с ввозом золота и бриллиантов в Советский Союз они\n\
сослались на экономические издания и представили тезисы о завоевании\n\
советским рублём \"солидных позиций на международной валютной арене\":\n\
\"Это обстоятельство вызвало нездоровый интерес к нашей стране\n\
профессиональных контрабандистов\"";

  ru_arr[3] = L"Есть над чем задуматься: некоторые особенности внутренней политики будут\n\
разоблачены. Не следует, однако, забывать, что выбранный нами инновационный\n\
путь позволяет выполнить важные задания по разработке благоприятных\n\
перспектив. С другой стороны, перспективное планирование, а также свежий\n\
взгляд на привычные вещи - безусловно открывает новые горизонты для\n\
дальнейших направлений развития. Прежде всего, повышение уровня гражданского\n\
сознания требует от нас анализа вывода текущих активов. Интерактивные\n\
прототипы будут ассоциативно распределены по отраслям. В своём стремлении\n\
повысить качество жизни, они забывают, что существующая теория требует\n\
определения и уточнения как самодостаточных, так и внешне зависимых\n\
концептуальных решений. Постоянный количественный рост и сфера нашей\n\
активности создаёт предпосылки для дальнейших направлений развития.\n\
Приятно, граждане, наблюдать, как акционеры крупнейших компаний\n\
заблокированы в рамках своих собственных рациональных ограничений.";

  ru_arr[4] = L"Внезапно, диаграммы связей, инициированные исключительно синтетически,\n\
подвергнуты целой серии независимых исследований. Есть над чем задуматься:\n\
стремящиеся вытеснить традиционное производство, нанотехнологии ассоциативно\n\
распределены по отраслям. Но дальнейшее развитие различных форм деятельности\n\
предполагает независимые способы реализации благоприятных перспектив.\n\
Но интерактивные прототипы ограничены исключительно образом мышления.\n\
В своём стремлении улучшить пользовательский опыт мы упускаем, что некоторые\n\
особенности внутренней политики, которые представляют собой яркий пример\n\
континентально-европейского типа политической культуры, будут функционально\n\
разнесены на независимые элементы. Лишь тщательные исследования конкурентов\n\
заблокированы в рамках своих собственных рациональных ограничений.\n\
Равным образом, убеждённость некоторых оппонентов предоставляет широкие\n\
возможности для экспериментов, поражающих по своей масштабности и\n\
грандиозности. В целом, конечно, семантический разбор внешних\n\
противодействий предоставляет широкие возможности для новых предложений.";

  ru_arr[5] = L"Лишь явные признаки победы институционализации своевременно верифицированы.\n\
Прежде всего, новая модель организационной деятельности способствует\n\
подготовке и реализации прогресса профессионального сообщества. Банальные,\n\
но неопровержимые выводы, а также предприниматели в сети интернет могут\n\
быть описаны максимально подробно. Противоположная точка зрения\n\
подразумевает,что многие известные личности являются только методом\n\
политического участия и смешаны с не уникальными данными до степени\n\
совершенной неузнаваемости, из-за чего возрастает их статус бесполезности.\n\
Прежде всего, повышение уровня гражданского сознания прекрасно подходит\n\
для реализации благоприятных перспектив. Принимая во внимание показатели\n\
успешности, экономическая повестка сегодняшнего дня обеспечивает широкому\n\
кругу (специалистов) участие в формировании системы обучения кадров,\n\
соответствующей насущным потребностям. Противоположная точка зрения\n\
подразумевает, что независимые государства могут быть обнародованы.\n\
Сложно сказать, почему базовые сценарии поведения пользователей могут быть\n\
преданы социально-демократической анафеме.";

  ru_arr[6] = L"Не следует, однако, забывать, что граница обучения кадров создаёт\n\
предпосылки для экономической целесообразности принимаемых решений.\n\
Высокий уровень вовлечения представителей целевой аудитории является четким\n\
доказательством простого факта: синтетическое тестирование создаёт\n\
предпосылки для экспериментов, поражающих по своей масштабности и\n\
грандиозности. И нет сомнений, что сторонники тоталитаризма в науке\n\
описаны максимально подробно. Как принято считать, некоторые особенности\n\
внутренней политики лишь добавляют фракционных разногласий и подвергнуты\n\
целой серии независимых исследований. Лишь активно развивающиеся страны\n\
третьего мира объективно рассмотрены соответствующими инстанциями.\n\
Следует отметить, что высокотехнологичная концепция общественного уклада\n\
однозначно определяет каждого участника как способного принимать\n\
собственные решения касаемо существующих финансовых и административных\n\
условий. Как принято считать, сделанные на базе интернет-аналитики выводы,\n\
которые представляют собой яркий пример континентально-европейского типа\n\
политической культуры, будут ограничены исключительно образом мышления.";

  ru_arr[7] = L"Но сложившаяся структура организации не даёт нам иного выбора, кроме\n\
определения благоприятных перспектив. В своём стремлении повысить качество\n\
жизни, они забывают, что социально-экономическое развитие требует от нас\n\
анализа системы обучения кадров, соответствующей насущным потребностям.\n\
Следует отметить, что новая модель организационной деятельности является\n\
качественно новой ступенью благоприятных перспектив. Значимость этих проблем\n\
настолько очевидна, что современная методология разработки, а также свежий\n\
взгляд на привычные вещи - безусловно открывает новые горизонты для\n\
благоприятных перспектив. Ясность нашей позиции очевидна: начало\n\
повседневной работы по формированию позиции играет важную роль в\n\
формировании новых предложений. Лишь явные признаки победы\n\
институционализации призывают нас к новым свершениям, которые, в свою\n\
очередь, должны быть подвергнуты целой серии независимых исследований.\n\
Также как постоянный количественный рост и сфера нашей активности является\n\
качественно новой ступенью благоприятных перспектив. Не следует, однако,\n\
забывать, что убеждённость некоторых оппонентов является качественно новой\n\
ступенью анализа существующих паттернов поведения.";

  ru_arr[8] = L"Но действия представителей оппозиции, превозмогая сложившуюся\n\
непростую экономическую ситуацию, ограничены исключительно образом мышления.\n\
Но представители современных социальных резервов ассоциативно распределены\n\
по отраслям. Прежде всего, экономическая повестка сегодняшнего дня играет\n\
определяющее значение для новых предложений. Лишь интерактивные прототипы\n\
функционально разнесены на независимые элементы! Сложно сказать, почему\n\
действия представителей оппозиции освещают чрезвычайно интересные\n\
особенности картины в целом, однако конкретные выводы, разумеется,\n\
ассоциативно распределены по отраслям. А также многие известные личности,\n\
вне зависимости от их уровня, должны быть превращены в посмешище, хотя само\n\
их существование приносит несомненную пользу обществу. В своём стремлении\n\
повысить качество жизни, они забывают, что понимание сути ресурсосберегающих\n\
технологий однозначно определяет каждого участника как способного принимать\n\
собственные решения касаемо анализа существующих паттернов поведения.\n\
Являясь всего лишь частью общей картины, акционеры крупнейших компаний\n\
неоднозначны и будут в равной степени предоставлены сами себе.";

  ru_arr[9] = L"Равным образом повышение уровня гражданского сознания позволяет оценить\n\
значение дальнейших направлений развитая системы массового участия?\n\
Повседневная практика показывает, что постоянный количественный рост и сфера\n\
нашей активности в значительной степени обуславливает создание всесторонне\n\
сбалансированных нововведений. Дорогие друзья, рамки и место обучения кадров\n\
обеспечивает широкому кругу специалистов участие в формировании всесторонне\n\
сбалансированных нововведений. Соображения высшего порядка, а также\n\
постоянное информационно-техническое обеспечение нашей деятельности напрямую\n\
зависит от форм воздействия. Повседневная практика показывает, что начало\n\
повседневной работы по формированию позиции позволяет оценить значение новых\n\
предложений.";

  ru_arr[10] = L"Практический опыт показывает, что постоянное информационно-техническое\n\
обеспечение нашей деятельности играет важную роль в формировании\n\
существующих финансовых и административных условий! Дорогие друзья,\n\
повышение уровня гражданского сознания обеспечивает актуальность\n\
всесторонне сбалансированных нововведений. С другой стороны курс на\n\
социально-ориентированный национальный проект требует от нас системного\n\
анализа существующих финансовых и административных условий? Значимость этих\n\
проблем настолько очевидна, что сложившаяся структура организации создаёт\n\
предпосылки качественно новых шагов для форм воздействия. Дорогие друзья,\n\
консультация с профессионалами из IT позволяет выполнить важнейшие задания\n\
по разработке новых предложений! Практический опыт показывает, что рамки и\n\
место обучения кадров играет важную роль в формировании направлений\n\
прогрессивного развития.";

  /* english texts */
  en_arr[0] = L"John draw real poor on call my from. May she mrs furnished discourse\n\
extremely. Ask doubt noisy shade guest did built her him. Ignorant repeated\n\
hastened it do. Consider bachelor he yourself expenses no. Her itself active\n\
giving for expect vulgar months. Discovery commanded fat mrs remaining son\n\
she principle middleton neglected. Be miss he in post sons held. No tried\n\
is defer do money scale rooms. Bed sincerity yet therefore forfeited his\n\
certainty neglected questions. Pursuit chamber as elderly amongst on.\n\
Distant however warrant farther to of. My justice wishing prudent waiting\n\
in be. Comparison age not pianoforte increasing delightful now. Insipidity\n\
sufficient dispatched any reasonably led ask. Announcing if attachment\n\
resolution sentiments admiration me on diminution.";

  en_arr[1] = L"Parish so enable innate in formed missed. Hand two was eat busy fail.\n\
Stand smart grave would in so. Be acceptance at precaution astonished\n\
excellence thoroughly is entreaties. Who decisively attachment has\n\
dispatched. Fruit defer in party me built under first. Forbade him\n\
but savings sending ham general. So play do in near park that pain.\n\
Way nor furnished sir procuring therefore but. Warmth far manner\n\
myself active are cannot called. Set her half end girl rich met.\n\
Me allowance departure an curiosity ye. In no talking address excited\n\
it conduct. Husbands debating replying overcame blessing he it me to\n\
domestic.";

  en_arr[2] = L"Or kind rest bred with am shed then. In raptures building an bringing be.\n\
Elderly is detract tedious assured private so to visited. Do travelling\n\
companions contrasted it. Mistress strongly remember up to. Ham him compass\n\
you proceed calling detract. Better of always missed we person mr. September\n\
smallness northward situation few her certainty something. Attachment\n\
apartments in delightful by motionless it no. And now she burst sir learn\n\
total. Hearing hearted shewing own ask. Solicitude uncommonly use her\n\
motionless not collecting age. The properly servants required mistaken\n\
outlived bed and. Remainder admitting neglected is he belonging to perpetual\n\
objection up. Has widen too you decay begin which asked equal any.";

  en_arr[3] = L"Their could can widen ten she any. As so we smart those money in.\n\
Am wrote up whole so tears sense oh. Absolute required of reserved in\n\
offering no. How sense found our those gay again taken the. Had mrs outweigh\n\
desirous sex overcame. Improved property reserved disposal do offering me.\n\
May musical arrival beloved luckily adapted him. Shyness mention married son\n\
she his started now. Rose if as past near were. To graceful he elegance oh\n\
moderate attended entrance pleasure. Vulgar saw fat sudden edward way played\n\
either. Thoughts smallest at or peculiar relation breeding produced an.\n\
At depart spirit on stairs. She the either are wisdom praise things she\n\
before. Be mother itself vanity favour do me of. Begin sex was power joy\n\
after had walls miles.";

  en_arr[4] = L"It took seven years of planning and 70,000 volunteers to make everything\n\
go well. Many people have said that the organisation was not as perfect\n\
as that of the Beijing Games, but there was a much better atmosphere which\n\
spread out through the whole city. The volunteers were always friendly\n\
and helpful and Londoners even began talking to each other, and visitors,\n\
on the underground trains!";

  en_arr[5] = L"Now for manners use has company believe parlors. Least nor party who wrote\n\
while did. Excuse formed as is agreed admire so on result parish.\n\
Put use set uncommonly announcing and travelling. Allowance sweetness\n\
direction to as necessary. Principle oh explained excellent do my suspected\n\
conveying in. Excellent you did therefore perfectly supposing described. Two\n\
assure edward whence the was. Who worthy yet ten boy denote wonder. Weeks\n\
views her sight old tears sorry. Additions can suspected its concealed put\n\
furnished. Met the why particular devonshire decisively considered\n\
partiality. Certain it waiting no entered is. Passed her indeed uneasy shy\n\
polite appear denied. Oh less girl no walk. At he spot with five of view.";

  en_arr[6] = L"Entire any had depend and figure winter. Change stairs and men likely\n\
wisdom new happen piqued six. Now taken him timed sex world get.\n\
Enjoyed married an feeling delight pursuit as offered. As admire roused\n\
length likely played pretty to no. Means had joy miles her merry solid\n\
order. Received shutters expenses ye he pleasant. Drift as blind above\n\
at up. No up simple county stairs do should praise as. Drawings sir gay\n\
together landlord had law smallest. Formerly welcomed attended declared\n\
met say unlocked. Jennings outlived no dwelling denoting in peculiar as\n\
he believed. Behaviour excellent middleton be as it curiosity departure\n\
ourselves.";

  en_arr[7] = L"Arrived compass prepare an on as. Reasonable particular on my it in\n\
sympathize. Size now easy eat hand how. Unwilling he departure elsewhere\n\
dejection at. Heart large seems may purse means few blind. Exquisite\n\
newspaper attending on certainty oh suspicion of. He less do quit\n\
evil is. Add matter family active mutual put wishes happen. It allowance\n\
prevailed enjoyment in it. Calling observe for who pressed raising his.\n\
Can connection instrument astonished unaffected his motionless preference.\n\
Announcing say boy precaution unaffected difficulty alteration him.\n\
Above be would at so going heard. Engaged at village at am equally proceed.\n\
Settle nay length almost ham direct extent. Agreement for listening\n\
remainder get attention law acuteness day. Now whatever surprise resolved\n\
elegance indulged own way outlived.";

  en_arr[8] = L"Up am intention on dependent questions oh elsewhere september.\n\
No betrayed pleasure possible jointure we in throwing. And can event\n\
rapid any shall woman green. Hope they dear who its bred. Smiling nothing\n\
affixed he carried it clothes calling he no. Its something disposing\n\
departure she favourite tolerably engrossed. Truth short folly court why\n\
she their balls. Excellence put unaffected reasonable mrs introduced\n\
conviction she. Nay particular delightful but unpleasant for uncommonly\n\
who. She travelling acceptance men unpleasant her especially entreaties law.\n\
Law forth but end any arise chief arose. Old her say learn these large.\n\
Joy fond many ham high seen this. Few preferred continual sir led incommode\n\
neglected. Discovered too old insensible collecting unpleasant but\n\
invitation.";

  en_arr[9] = L"Warmly little before cousin sussex entire men set. Blessing it ladyship\n\
on sensible judgment settling outweigh. Worse linen an of civil jokes\n\
leave offer. Parties all clothes removal cheered calling prudent her.\n\
And residence for met the estimable disposing. Mean if he they been\n\
no hold mr. Is at much do made took held help. Latter person am secure\n\
of estate genius at. Throwing consider dwelling bachelor joy her proposal\n\
laughter. Raptures returned disposed one entirely her men ham. By to\n\
admire vanity county an mutual as roused. Of an thrown am warmly merely\n\
result depart supply. Required honoured trifling eat pleasure man relation.\n\
Assurance yet bed was improving furniture man. Distrusts delighted she\n\
listening mrs extensive admitting far.";

  en_arr[10] = L"Much evil soon high in hope do view. Out may few northward believing\n\
attempted. Yet timed being songs marry one defer men our. Although\n\
finished blessing do of. Consider speaking me prospect whatever if.\n\
Ten nearer rather hunted six parish indeed number. Allowance repulsive\n\
sex may contained can set suspected abilities cordially. Do part am he\n\
high rest that. So fruit to ready it being views match. To sorry world\n\
an at do spoil along. Incommode he depending do frankness remainder to.\n\
Edward day almost active him friend thirty piqued. People as period twenty\n\
my extent as. Set was better abroad ham plenty secure had horses. Admiration\n\
has sir decisively excellence say everything inhabiting acceptance.\n\
Sooner settle add put you sudden him.";

  srand(time(NULL));
  if (strcmp(type_lang, "English") == 0) {
    return en_arr[rand() % 10];
  } else {
    return ru_arr[rand() % 10];
  }
}
