# Voyager Status

This is a Bash script to calculate how far away Voyager 1 and 2 are from the Sun.

![Example image showing the script in use with Voyager 1 and 2](/example.png)

To use it, you can just download it and run `./voyagerstatus.sh`. This will run Voyager Status with the default settings, which display Voyager 1's distance in kilometers.

I made this to put in my `.bashrc` so I get a little reminder every time I open my terminal.

## Installing

You can run the .sh file directly after downloading, but you can also add it to your PATH for easier access.

These instructions assume zero knowledge of setting up a command and provide reasonable defaults for new users.

1. Create `~/.local/bin` if it doesn't already exist.
2. Move `voyagerstatus.sh` to `~/.local/bin`.
3. Rename `voyagerstatus.sh` to just `voyagerstatus`.
4. Make sure `~/.local/bin` is in your PATH ([see here for a how-to](https://www.howtogeek.com/658904/how-to-add-a-directory-to-your-path-in-linux/)).
5. Now you can run `voyagerstatus` from your terminal.

## Options

There are a handful of launch options available.

You can add as many launch arguments as you want, but only the final argument in each category will take effect.

### Distance units

`-k`: Show the distance in kilometers (default)   
`-m`: Show the distance in miles   

I want to add support for Astronomical Units in the future.

### Pick a probe

`-v1`: Display the distance of Voyager 1 (default)   
`-v2`: Display the distance of Voyager 2   

### Color

You can optionally choose a color to print the text in.

The argument to set the color is `-color=name` where `name` is:

* red
* blue
* green
* cyan
* black
* yellow
* purple
* white

## Examples:

```bash
$ ./voyagerstatus.sh -v2 -m
Voyager 2 is 12,045,896,105 miles from the Sun.
```

```bash
$ ./voyagerstatus.sh -v1 -color=red
Voyager 1 is 23,294,958,078 kilometers from the Sun.
# You can't see the color here on GitHub.
```

```bash
$ ./voyagerstatus.sh
Voyager 1 is 23,294,959,098 kilometers from the Sun.
```

## Other info

Voyager Status only shows one Voyager at a time. If you want to show both Voyager 1 and 2, you should run the command twice with the relevant launch options.

I want to add an option for distance from the Earth, because that sounds a lot more interesting. But it requires some extra math due to the Earth's orbit. In fact, for part of the year the Voyager probes get *closer* to Earth, because the Earth's orbit moves us toward the Voyagers at a faster velocity than the Voyagers are moving away. So it'll be a bit of a challenge to pin down the math for that. But I plan to do it.