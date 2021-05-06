#include <string.h>
#include <stdlib.h>
#include <time.h>

wchar_t *generate_text(char *type_lang)
{
  wchar_t *ru_arr[15];
  wchar_t *en_arr[15];

  /* russion texts */
  ru_arr[0] = L"Разнообразный и богатый опыт говорит нам, что постоянное\n\
информационно-пропагандистское обеспечение нашей деятельности позволяет\n\
выполнить важные задания по разработке стандартных подходов. Значимость\n\
этих проблем настолько очевидна, что базовый вектор развития является\n\
качественно новой ступенью поэтапного и последовательного развития общества.\n\
Прежде всего, современная методология разработки напрямую зависит от как\n\
самодостаточных, так и внешне зависимых концептуальных решений. Являясь\n\
всего лишь частью общей картины, базовые сценарии поведения пользователей\n\
обнародованы. Также как синтетическое тестирование позволяет выполнить\n\
важные задания по разработке распределения внутренних резервов и ресурсов!\n\
Высокий уровень вовлечения представителей целевой аудитории является четким\n\
доказательством простого факта: базовый вектор развития требует от нас\n\
анализа существующих финансовых и административных условий. Мы вынуждены\n\
отталкиваться от того, что новая модель организационной деятельности говорит\n\
о возможностях глубокомысленных рассуждений.";

  ru_arr[1] = L"Мы вынуждены отталкиваться от того, что выбранный нами инновационный путь\n\
напрямую зависит от позиций, занимаемых участниками в отношении поставленных\n\
задач! Для современного мира высококачественный прототип будущего проекта\n\
представляет собой интересный эксперимент проверки существующих финансовых\n\
и административных условий. Есть над чем задуматься: предприниматели в сети\n\
интернет, которые представляют собой яркий пример континентально-европейского\n\
типа политической культуры, будут ограничены исключительно образом мышления.\n\
В рамках спецификации современных стандартов, некоторые особенности\n\
внутренней политики формируют глобальную экономическую сеть и при этом,\n\
описаны максимально подробно. Равным образом, укрепление и развитие\n\
внутренней структуры играет важную роль в формировании новых принципов\n\
формирования материально-технической и кадровой базы. В целом, конечно,\n\
укрепление и развитие внутренней структуры обеспечивает широкому кругу\n\
(специалистов) участие в формировании переосмысления внешнеэкономических\n\
политик. А ещё интерактивные прототипы неоднозначны и будут в равной степени\n\
предоставлены сами себе.";

  ru_arr[2] = L"Идею нового фильма предложил Яков Костюковский, прочитавший\n\
в журнале \"За рубежом\" заметку о европейских мошенниках, использовавших для\n\
перевозки ценностей гипсовые повязки, которые накладывались на месте мнимых\n\
переломов. Эта сюжетная канва с перемещением основного действия в СССР\n\
показалась режиссёру интересной, и в марте 1967 года соавторы направили на\n\
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
подразумевает, что многие известные личности являются только методом\n\
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

  ru_arr[9] = L"С другой стороны, базовый вектор развития говорит о возможностях\n\
приоритизации разума над эмоциями. Как принято считать, явные признаки\n\
победы институционализации преданы социально-демократической анафеме.\n\
Прежде всего, повышение уровня гражданского сознания играет определяющее\n\
значение для как самодостаточных, так и внешне зависимых концептуальных\n\
решений. Как принято считать, интерактивные прототипы объявлены нарушающими\n\
общечеловеческие нормы этики и морали. С учётом сложившейся международной\n\
обстановки, понимание сути ресурсосберегающих технологий выявляет срочную\n\
потребность дальнейших направлений развития. В рамках спецификации\n\
современных стандартов, тщательные исследования конкурентов функционально\n\
разнесены на независимые элементы. В частности, понимание сути\n\
ресурсосберегающих технологий, в своём классическом представлении, допускает\n\
внедрение первоочередных требований. В целом, конечно, укрепление и развитие\n\
внутренней структуры не оставляет шанса для инновационных методов управления\n\
процессами!";

  ru_arr[10] = L"В своём стремлении улучшить пользовательский опыт мы упускаем, что ключевые\n\
особенности структуры проекта лишь добавляют фракционных разногласий и\n\
своевременно верифицированы. Лишь акционеры крупнейших компаний освещают\n\
чрезвычайно интересные особенности картины в целом, однако конкретные\n\
выводы, разумеется, смешаны с не уникальными данными до степени совершенной\n\
неузнаваемости, из-за чего возрастает их статус бесполезности. Равным\n\
образом, перспективное планирование, в своём классическом представлении,\n\
допускает внедрение своевременного выполнения сверхзадачи. А ещё сторонники\n\
тоталитаризма в науке могут быть объявлены нарушающими общечеловеческие\n\
нормы этики и морали. Предварительные выводы неутешительны: консультация с\n\
широким активом однозначно определяет каждого участника как способного\n\
принимать собственные решения касаемо инновационных методов управления\n\
процессами. Имеется спорная точка зрения, гласящая примерно следующее:\n\
представители современных социальных резервов могут быть объявлены\n\
нарушающими общечеловеческие нормы этики и морали. Приятно, граждане,\n\
наблюдать, как базовые сценарии поведения пользователей преданы\n\
социально-демократической анафеме.";

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

  en_arr[3] = L"Extremity sweetness difficult behaviour he of. On disposal of as landlord\n\
horrible. Afraid at highly months do things on at. Situation recommend\n\
objection do intention so questions. As greatly removed calling pleased\n\
improve an. Last ask him cold feel met spot shy want. Children me laughing\n\
we prospect answered followed. At it went is song that held help face.\n\
Alteration literature to or an sympathize mr imprudence. Of is ferrars\n\
subject as enjoyed or tedious cottage. Procuring as in resembled by in\n\
agreeable. Next long no gave mr eyes. Admiration advantages no he celebrated\n\
so pianoforte unreserved. Not its herself forming charmed amiable. Him why\n\
feebly expect future now.";

  en_arr[4] = L"Started earnest brother believe an exposed so. Me he believing daughters if\n\
forfeited at furniture. Age again and stuff downs spoke. Late hour new nay\n\
able fat each sell. Nor themselves age introduced frequently use unsatiable\n\
devonshire get. They why quit gay cold rose deal park. One same they four\n\
did ask busy. Reserved opinions fat him nay position. Breakfast as zealously\n\
incommode do agreeable furniture. One too nay led fanny allow plate. An an\n\
valley indeed so no wonder future nature vanity. Debating all she mistaken\n\
indulged believed provided declared. He many kept on draw lain song as same.\n\
Whether at dearest certain spirits is entered in to. Rich fine bred real use\n\
too many good. She compliment unaffected expression favourable any. Unknown\n\
chiefly showing to conduct no. Hung as love evil able to post at as.";

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

  en_arr[6] = L"Offered say visited elderly and. Waited period are played family man formed.\n\
He ye body or made on pain part meet. You one delay nor begin our folly\n\
abode. By disposed replying mr me unpacked no. As moonlight of my resolving\n\
unwilling. Suppose end get boy warrant general natural. Delightful met\n\
sufficient projection ask. Decisively everything principles if preference do\n\
impression of. Preserved oh so difficult repulsive on in household. In what\n\
do miss time be. Valley as be appear cannot so by. Convinced resembled\n\
dependent remainder led zealously his shy own belonging. Always length\n\
letter adieus add number moment she. Promise few compass six several old\n\
offices removal parties fat. Concluded rapturous it intention perfectly\n\
daughters is as.";

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

  en_arr[10] = L"Now indulgence dissimilar for his thoroughly has terminated. Agreement\n\
offending commanded my an. Change wholly say why eldest period. Are\n\
projection put celebrated particular unreserved joy unsatiable its. In then\n\
dare good am rose bred or. On am in nearer square wanted. Silent sir say\n\
desire fat him letter. Whatever settling goodness too and honoured she\n\
building answered her. Strongly thoughts remember mr to do consider\n\
debating. Spirits musical behaved on we he farther letters. Repulsive\n\
he he as deficient newspaper dashwoods we. Discovered her his pianoforte\n\
insipidity entreaties. Began he at terms meant as fancy. Breakfast arranging\n\
he if furniture we described on. Astonished thoroughly unpleasant especially\n\
you dispatched bed favourable.";

  srand(time(NULL));
  if (strcmp(type_lang, "English") == 0) {
    return en_arr[rand() % 10];
  } else {
    return ru_arr[rand() % 10];
  }
}
