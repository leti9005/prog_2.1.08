const fs = require('fs');

class ReplaceCommand {
    constructor(targetSentenceIndex, wordEnding, replaceWith = '') {
        this.targetSentenceIndex = +targetSentenceIndex;

        this.wordEnding = wordEnding;
        this.replaceWith = replaceWith;
    }

    applyTo(text) {
        // Разберём по частям в `text` написанное.
        const textSentences = text.split`.`;
        const sentence = textSentences[this.targetSentenceIndex];

        const words = sentence.split` `;

        let wordIndex = -2;

        while (wordIndex !== -1) {
            wordIndex = words.findIndex(w => w.endsWith(this.wordEnding));

            words[wordIndex] = this.replaceWith;
        }

        // Соберём обратно.
        const newSentence = words.join` `;
        textSentences[this.targetSentenceIndex] = newSentence;

        const newText = textSentences.join`.`;
        return newText;
    }
}

function getCommandsFromArgs(args) {
    const commands = [];

    for (let i = 0; i < args.length;) {
        const arg = args[i];

        const sentenceIndex = +arg.substr(2);

        const command = new ReplaceCommand(sentenceIndex, args[i + 1]);
        const type = arg[1];

        if (type === 'r') {
            command.replaceWith = args[i + 2];
            i += 3;
        }
        else {
            i += 2;
        }

        commands.push(command);
    }

    return commands;
}

const inputFile = process.argv[2];
const outputFile = process.argv[3];

const args = process.argv.slice(4);

console.log(args);

const commands = getCommandsFromArgs(args);

console.log(commands);

const fsOptions = { encoding: 'UTF-8' };

let text = fs.readFileSync(inputFile, fsOptions);

for (const c of commands) {
    text = c.applyTo(text);
}

fs.writeFileSync(outputFile, text, fsOptions);
