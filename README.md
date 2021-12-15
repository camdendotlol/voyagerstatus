# Voyager Status

This is a Bash script to calculate how far away Voyager 1 and 2 are from Earth.

![Example image showing the script in use with Voyager 1 and 2](/example.png)

To use it, you can just download it and run `./voyagerstatus.sh`. This will run Voyager Status with the default settings, which display Voyager 1's distance in kilometers.

I made this to put in my `.bashrc` so I get a little reminder every time I open my terminal.

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

The argument to set the color is `color=name` where `name` is:

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
Voyager 2 is 12,045,896,105 miles away.
```

```bash
$ ./voyagerstatus.sh -v1 color=red
Voyager 1 is 23,294,958,078 kilometers away.
# You can't see the color here on GitHub.
```

```bash
$ ./voyagerstatus.sh
Voyager 1 is 23,294,959,098 kilometers away.
```

## Other info

Voyager Status only shows one Voyager at a time. If you want to show both Voyager 1 and 2, you should run the command twice with the relevant launch options.