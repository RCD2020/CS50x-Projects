let container = document.getElementById('ingredients');
const attrNames = [
    'Cure Disease', 'Damage Health', 'Damage Magicka', 'Damage Magicka Regen',
    'Damage Stamina', 'Damage Stamina Regen', 'Fear', 'Fortify Barter',
    'Fortify Block', 'Fortify Carry Weight', 'Fortify Conjuration',
    'Fortify Destruction', 'Fortify Enchanting', 'Fortify Health',
    'Fortify Heavy Armor', 'Fortify Illusion', 'Fortify Lockpicking',
    'Fortify Magicka', 'Fortify Marksman', 'Fortify One-handed',
    'Fortify Pickpocket', 'Fortify Smithing', 'Fortify Sneak',
    'Fortify Stamina', 'Frenzy', 'Invisibility', 'Lingering Damage Health',
    'Lingering Damage Magicka', 'Lingering Damage Stamina', 'Ravage Health',
    'Ravage Magicka', 'Ravage Stamina', 'Regenerate Health', 'Regenerate Magicka',
    'Resist Fire', 'Resist Frost', 'Resist Magic', 'Resist Poison', 'Resist Shock',
    'Restore Health', 'Restore Magicka', 'Restore Stamina', 'Slow', 'Waterbreathing',
    'Weakness to Fire', 'Weakness to Frost', 'Weakness to Magic', 'Weakness to Poison',
    'Weakness to Shock'
];

let key;
for (var i = 0; i < localStorage.length; i++)
{
    key = localStorage.key(i);
    show(key);
}


function updateIndex(key, index)
{
    let data = localStorage.getItem(key);
    data = data.slice(0, index) + '0' + data.slice(index);
    localStorage.setItem(key, data);
    return data;
}


function updateData(key)
{
    let data = localStorage.getItem(key);
    // Waterbreathing update index 43
    if (data.length == 48)
    {
        data = updateIndex(key, 43);
    }

    return data;
}


function show(key)
{
    let element = '';
    element += '<div id="' + key + '">';

    let value = localStorage.getItem(key)
    if (value.length < attrNames.length)
    {
        value = updateData(key);
    }
    element += '<h3>' + key + '</h3>';
    let keyId = key.replace(/ /g, '_');

    element += '<button onclick="clearOne(\'' + keyId + '\')">Clear</button><br>';

    let text;
    for (var i = 0; i < attrNames.length; i++)
    {
        element += '<label>';
        text = '<input id="' + keyId + '.' + i + '" type="checkbox" onclick="updateIn(\'' + keyId + '.' + i + '\')" ';
        if (value[i] == '1')
        {
            text += 'checked ';
        }
        text += '/>';

        element += text;
        element += attrNames[i];
        element += '</label>';
        element += '<br>';
    }

    element += '</div>';
    element += '<br>';

    container.innerHTML += element;
}


function newIn()
{
    let input = document.getElementById('newIn');
    let name = input.value;

    if (name == '' || localStorage.getItem(name) != null)
    {
        return;
    }

    input.value = '';
    let value = '';
    for (var i = 0; i < attrNames.length; i++)
    {
        value += '0';
    }

    localStorage.setItem(name, value);
    show(name);
}


function clearIn()
{
    container.innerHTML = '';
    localStorage.clear();
}


function updateIn(id)
{
    let key = id.split('.')[0].replace(/_/g, ' ');
    let attr = parseInt(id.split('.')[1]);
    let data = localStorage.getItem(key);
    let value;
    if (document.getElementById(id).checked)
    {
        value = '1';
    }
    else
    {
        value = '0';
    }

    data = data.slice(0, attr) + value + data.slice(attr + 1);
    localStorage.setItem(key, data);
}


function clearOne(id)
{
    let key = id.replace(/_/g, ' ');
    element = document.getElementById(key);
    element.remove();
    localStorage.removeItem(key);
}