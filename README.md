# coprintf #

Colorful printf for C Code ( ascii color only ), decorate your terminal with more colors.

### Overview ###

A light, self-adapting wrapper of `printf` with several useful features, makes easy work for changing **foreground**, **background** and **text action** ( highlight, underline, blink ... ) . It makes you easy to enable and disable colorizing in your c&cpp's output.

#### Screenshot ####

##### Active #####

![screenshot](https://raw.github.com/springlie/coprintf/master/screenshot.png)

##### Inactive #####

![screenshot](https://raw.github.com/springlie/coprintf/master/screenshot2.png)

#### Example ####

##### set *fg* to red: #####
	
	coprintf("^r%s","hello world !");

or

	coprintf("^rhello world !");

##### set *fg* to red, *bg* to yellow, *action* to highlight and underline: #####

	coprintf("^r^Y^h^u%s","hello world !");

##### set [ *red*, *yellow*, *highlight* & *underline* ] for "hello", [ *cyan*, *red*, *reverse* ] for "world", [ *green*, *black*, *blink* ] for "!" : #####

	coprintf("^r^Y^h^u%shello^d ^c^R^eworld^d ^g^K^l!");

Please refer to [**demo.c**](https://github.com/springlie/coprintf/blob/master/demo.c) for more examples:

### Install ###

Simply include the header in your files, like this:

`#include "coprintf.h"`

### Usage ###

#### Syntax ####

##### Support multi-string in one command: #####

	coprintf("<leader>rHello <leader>bWorld");

	ceprintf("<leader>rHello <leader>bWorld");

##### Support setting foreground, background and action #####

	coprintf("<leader>r<leader>YHello <leader>b<leader>CWorld");

	ceprintf("<leader>r<leader>YHello <leader>b<leader>CWorld");

##### Support status switch via macro: #####

| macro CO_PRINTF_INACTIVE defined ? | colorize     |
| ---------------------------------- | ------------ |
| yes                                | not colorful |
| no                                 | colorful     |

##### Support status automatical switch via output fd: #####

| output fd	| colorize     |
| --------- | ------------ |
| not tty	| not colorful |
| tty       | colorful     |

**What's `<Leader>` Character ?**

We define a character as the `<leader>` which will combine the mode character as an escape character.

The default `<leader>` is **"^"**, but you can customize it to any char you want.


#### Mode flag ####

##### Foreground color flag #####

| mode		  | color  |
| ----------- | ------ |
| `<leader>`k | black  |
| `<leader>`r | red    |
| `<leader>`g | green  |
| `<leader>`y | yellow |
| `<leader>`b | blue   |
| `<leader>`p | purple |
| `<leader>`c | cyan   |
| `<leader>`w | write  |

##### Background color flag #####

| mode        | color  |
| ----------- | ------ |
| `<leader>`K | black  |
| `<leader>`R | red    |
| `<leader>`G | green  |
| `<leader>`Y | yellow |
| `<leader>`B | blue   |
| `<leader>`P | purple |
| `<leader>`C | cyan   |
| `<leader>`W | write  |

##### Action flag #####

| mode		  | action    |
| ----------- | --------- |
| `<leader>`d | done      |
| `<leader>`h | highlight |
| `<leader>`u | underline |
| `<leader>`e | reverse   |
| `<leader>`l | blink     |
| `<leader>`v | invisible |

The mode control formats are easily memorized:

1. Foreground : **almost** the lowercase of color mode head, "black" is exceptive.
	
2. Background : **almost** the uppercase of color mode head, "black" is exceptive.

3. Controling : **almost** the lowercase of mode head, with some exceptions.

#### Macro ####

You can customize the below Macros in [**coprintf.h**](https://github.com/springlie/coprintf/blob/master/coprintf.h):

##### CO_PRINTF_INACTIVE #####

Default: not set.

`coprintf` will be disabled if `CO_PRINTF_INACTIVE` is set in `coprintf.h` like this:

	#define CO_PRINTF_INACTIVE

Or compiling with option like this:

	-DCO_PRINTF_INACTIVE

##### CO_PRINTF_LEADER #####

Default: '^'

The `<leader>` char can be customized by `CO_PRINTF_LEADER`:

	/* set '#' as the <leader> char*/
	#define CO_PRINTF_LEADER	'#'

## Advanced ##

- `coprintf` is self-adapting. When the colorful output is redirected to other file, `coprintf` will disabled color automatically.
- Action flag `<leader>d` will turn off all settings ( fg, bg and action ), Thus, in **single** command, you have to set flags again to make it work well once there are other strings after `<leader>d`.
- If you want to print the <leader> itself, try `<leader><leader>`; If the char after leader isn't defined as an escape char, it will be ignored.
- It's **not** necessary use `<leader>d` at the begin/end of commands, `coprintf` do it automatically.
- Actions can overlaied.

## What's more ##

This project is really same as [**cecho**](https://github.com/springlie/cecho), which supports similar functions to `echo` in shell script.
